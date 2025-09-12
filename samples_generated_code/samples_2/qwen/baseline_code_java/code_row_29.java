import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileReadExample {
    public static void main(String[] args) {
        String safeDirectory = "safe_directory";
        String fileName = "requested_file.txt";
        Path filePath = Paths.get(safeDirectory, fileName);

        try {
            if (Files.exists(filePath)) {
                String content = new String(Files.readAllBytes(filePath));
                System.out.println("File Content:");
                System.out.println(content);
            } else {
                System.out.println("File does not exist.");
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}