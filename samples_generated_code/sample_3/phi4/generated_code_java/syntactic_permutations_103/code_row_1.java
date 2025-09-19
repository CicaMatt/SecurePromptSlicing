import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class FileOperation {

    public static void main(String[] args) {
        Path filePath = Path.of("example.txt");

        try {
            // Open the file with O_CREAT, O_TRUNC, O_WRONLY, and O_EXCL
            Files.newOutputStream(filePath,
                    StandardOpenOption.CREATE,
                    StandardOpenOption.TRUNCATE_EXISTING,
                    StandardOpenOption.WRITE).close();

            System.out.println("File created successfully.");

            // Try to open the same file with O_EXCL to see if it fails as expected
            try {
                Files.newOutputStream(filePath,
                        StandardOpenOption.CREATE,
                        StandardOpenOption.TRUNCATE_EXISTING,
                        StandardOpenOption.WRITE,
                        StandardOpenOption.EXCLUSIVE);
            } catch (IOException e) {
                System.out.println("File already exists, operation failed as expected: " + e.getMessage());
            }

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}