import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "important_config";
        String content = "important_config\n";

        try {
            // Create the file if it doesn't exist and set appropriate permissions
            Files.createFile(Paths.get(filePath));
            
            // Set read/write for owner, read for group and others
            File file = new File(filePath);
            boolean success = file.setReadable(true, false) &&
                              file.setWritable(true, false) &&
                              file.setReadable(true, true) &&
                              file.setReadable(true, true);

            if (success) {
                // Open the file with options to create if not exists and write
                Files.write(Paths.get(filePath), content.getBytes(), StandardOpenOption.CREATE, StandardOpenOption.WRITE);
                
                System.out.println("File written successfully.");
            } else {
                System.err.println("Failed to set appropriate permissions on the file.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}