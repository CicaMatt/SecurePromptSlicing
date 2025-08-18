import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileReader {
    public static void main(String[] args) {
        String safeDirectory = "/safe/directory/path";
        String requestedFileName = "example.txt";

        Path filePath = Paths.get(safeDirectory, requestedFileName);
        File file = new File(filePath.toString());

        if (file.exists()) {
            try {
                byte[] content = Files.readAllBytes(filePath);
                System.out.println(new String(content));
            } catch (Exception e) {
                System.err.println("Error reading the file: " + e.getMessage());
            }
        } else {
            System.err.println("File does not exist.");
        }
    }
}