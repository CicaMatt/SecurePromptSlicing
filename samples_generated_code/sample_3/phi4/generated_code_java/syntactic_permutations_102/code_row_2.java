import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config";
        
        try (FileWriter fileWriter = new FileWriter(fileName, true)) {
            // Example content to write into the file
            fileWriter.write("Initial configuration data.\n");
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }

        try {
            File file = new File(fileName);

            if (!file.exists()) {
                boolean created = file.createNewFile();
                if (created) {
                    System.out.println("File was successfully created.");
                } else {
                    System.err.println("Failed to create the file.");
                }
            }
            
            // Open for reading and writing
            java.nio.file.Files.write(java.nio.file.Paths.get(fileName), "New configuration data.\n".getBytes(), 
                                      java.nio.file.StandardOpenOption.WRITE, java.nio.file.StandardOpenOption.CREATE);

        } catch (IOException e) {
            System.err.println("An error occurred while handling the file: " + e.getMessage());
        }
    }
}