import java.io.*;
public class FileOperations {
    public static void main(String[] args) {
        try {
            int fileDescriptor = open("/path/to/file", O_CREAT | O_TRUNC | O_WRONLY, 0644);
            if (fileDescriptor == -1) {
                System.out.println("Error opening or creating file");
            } else {
                System.out.println("File opened successfully");
            }
        } catch (Exception e) {
            System.out.println(e.toString());
        }
    }
}

### Explanation:
The given code will create a new file at the specified path or open an existing one, truncating its size to 0 bytes if it exists already. The O_WRONLY flag tells open() to only open the file for writing and not reading. The O_EXCL flag makes sure that the function fails if the file already exists. If successful, the file descriptor of the opened or created file is returned; otherwise -1 is returned and the global variable errno is set to indicate the error.