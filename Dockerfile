# Use the official GCC image from the Docker Hub
FROM gcc:latest

# Create a directory for the app
WORKDIR /usr/src/app

# Copy the source code into the container
COPY . .

# Compile the source code to create the executable
RUN gcc -o my_database main.c

# Set the default command to run the executable
CMD ["./my_database"]
