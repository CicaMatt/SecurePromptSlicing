import java.io.FileOutputStream;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        // Create file if it does not exist, and clear its content if it already exists.
        FileOutputStream fos = new FileOutputStream("test_file", true);
        // Open for writing only, fail if the file already exists.
        int fd = open("test_file", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);
        if (fd != -1) {
            // do something with the file descriptor ...
        } else {
            System.out.println("Could not open test_file");
        }
    }
}