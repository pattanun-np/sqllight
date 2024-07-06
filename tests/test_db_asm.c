#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to run database commands
char **run_script(char *script[], int count)
{
    int pipefd[2], pipefd_in[2];
    if (pipe(pipefd) == -1 || pipe(pipefd_in) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    { // Child process
        close(pipefd[0]);
        close(pipefd_in[1]);
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd_in[0], STDIN_FILENO);
        close(pipefd[1]);
        close(pipefd_in[0]);
        execvp("./build_asm/db", (char *[]){"./build_asm/db", "./build_asm/test.db", NULL});
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    close(pipefd[1]);
    close(pipefd_in[0]);
    FILE *fp_in = fdopen(pipefd_in[1], "w");
    FILE *fp = fdopen(pipefd[0], "r");

    for (int j = 0; j < count; j++)
    {
        fprintf(fp_in, "%s\n", script[j]);
    }
    fflush(fp_in);
    close(pipefd_in[1]);

    char **output = malloc(sizeof(char *) * count);
    for (int i = 0; i < count; i++)
    {
        output[i] = malloc(256);
        if (fgets(output[i], 256, fp) == NULL)
        {
            free(output[i]);
            output[i] = NULL;
            break;
        }
    }
    fclose(fp);
    waitpid(pid, NULL, 0);
    return output;
}

double benchmark_inserts_and_selects(int num_operations)
{
    char **script = malloc(sizeof(char *) * (num_operations * 2 + 1));
    for (int i = 0; i < num_operations; i++)
    {
        script[2 * i] = malloc(50);
        sprintf(script[2 * i], "insert %d user%d person%d@example.com", i + 1, i + 1, i + 1);
        script[2 * i + 1] = strdup("select");
    }
    script[num_operations * 2] = strdup(".exit");
    int count = num_operations * 2 + 1;

    clock_t start = clock();
    char **result = run_script(script, count);
    clock_t end = clock();

    for (int i = 0; i < count; i++)
    {
        if (result[i])
        {
            free(result[i]);
        }
        free(script[i]);
    }
    free(script);
    free(result);

    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main()
{
    int n_runs = 10; // Number of times to run the benchmark
    double total_time = 0;

    for (int i = 0; i < n_runs; i++)
    {
        system("rm -rf ./build_asm/test.db");                   // Setup - Remove existing database
        double time_spent = benchmark_inserts_and_selects(1000); // Run benchmark
        printf("Run %d: %.6f seconds\n", i + 1, time_spent);
        total_time += time_spent;
    }

    printf("Average time: %.6f seconds\n", total_time / n_runs);

    return 0;
}
