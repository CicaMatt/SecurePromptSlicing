import java.io.*;

public class FileCreate {
    public static void main(String[] args) {
        int fd = 0;
        try {
            //create a new file or opens an existing file
            //O_CREAT flag tells open() to create if it doesn't exist
            //O_TRUNC flag tells open() to truncate to 0 bytes if it already exists.
            fd = open("file.txt", O_WRONLY | O_CREAT | O_EXCL);
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}