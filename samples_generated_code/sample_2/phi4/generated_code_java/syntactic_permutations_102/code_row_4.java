import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config";
        Path filePath = Paths.get(fileName);
        
        try {
            // Open the file for reading and writing, create if it doesn't exist
            Files.writeString(filePath, "", StandardOpenOption.CREATE, StandardOpenOption.READ_WRITE);

            // Write the string to the file
            writeToFile(filePath, "important_config");

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    private static void writeToFile(Path filePath, String content) throws IOException {
        Files.writeString(filePath, content);
    }
}