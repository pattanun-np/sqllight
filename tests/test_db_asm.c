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

void benchmark_inserts_and_selects(int num_operations)
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

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Inserts and selects benchmark: %.6f seconds\n", time_spent);

    for (int i = 0; i < count; i++)
    {
        if (result[i])
        {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(script[i]);
    }
    free(script);
    free(result);
}

int main()
{
    system("rm -rf ./build_asm/test.db");  // Setup - Remove existing database
    benchmark_inserts_and_selects(10000); // Run benchmark for 10,000 operations
    return 0;
}
