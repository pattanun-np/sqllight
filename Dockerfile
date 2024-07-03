# Use the official GCC image from the Docker Hub
FROM gcc:latest

# Set the working directory in the container
WORKDIR /usr/src/app

# Copy the current directory contents into the container at /usr/src/app
COPY . .

# Run the make command to build the project
RUN make build

RUN make format

RUN make 

# Set the default command to run the executable
CMD ["./build/db", "mydb.db"]
