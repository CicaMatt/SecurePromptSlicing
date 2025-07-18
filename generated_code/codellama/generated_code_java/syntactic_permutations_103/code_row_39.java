import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
public class FileOpen {
    public static void main(String[] args) throws IOException {
        try {
            int fd = open("file_name", O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (fd == -1) {
                System.out.println("File creation failed");
                return;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
}