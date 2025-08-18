import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "important_config.txt";
        String contentToWrite = "Important configuration data";

        try {
            // Open file with O_RDWR (read/write) and O_CREAT (create if not exists)
            Path path = Paths.get(filePath);
            Files.write(path, contentToWrite.getBytes(), StandardOpenOption.CREATE, StandardOpenOption.WRITE);

            System.out.println("File written successfully.");
        } catch (IOException e) {
            System.err.println("Error occurred while writing to file: " + e.getMessage());
        }
    }
}