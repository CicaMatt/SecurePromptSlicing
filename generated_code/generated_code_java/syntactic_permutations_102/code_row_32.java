import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        int fd;
        char[] buffer = new char[1024];
        
        fd = open("important_config", O_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd == -1) {
            System.out.println("Error opening file!");
            return;
        }
        
        // write to the file
        buffer[0] = 'a';
        buffer[1] = '\n';
        write(fd, buffer, 2);
        
        // read from the file
        read(fd, buffer, 1);
        System.out.println("First character: " + buffer[0]);
    }
}