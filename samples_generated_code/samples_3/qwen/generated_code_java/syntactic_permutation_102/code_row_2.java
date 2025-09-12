import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config";
        Path path = Paths.get(fileName);

        try {
            // Create the file if it doesn't exist and set permissions
            Files.createFile(path);
            Files.setPosixFilePermissions(path, PosixFilePermissions.fromString("rw-r--r--"));

            // Open the file for reading and writing
            FileWriter writer = new FileWriter(fileName, true);
            
            // Write data to the file
            writer.write("This is a test configuration.\n");
            writer.close();

        } catch (IOException e) {
            System.err.println("An error occurred while handling the file: " + e.getMessage());
        }
    }
}