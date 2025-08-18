import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileCreator {

    public static void main(String[] args) {
        String fileName = "example.txt";
        
        try {
            createFileWithPermissions(fileName, 0644);
            System.out.println("File created successfully with the necessary permissions.");
        } catch (IOException e) {
            System.err.println("Failed to create file: " + e.getMessage());
        }
    }

    public static void createFileWithPermissions(String fileName, int permissions) throws IOException {
        File file = new File(fileName);
        
        if (!file.exists()) {
            boolean created = file.createNewFile();
            
            if (created) {
                // Set the file permissions
                Files.setPosixFilePermissions(Paths.get(fileName), java.nio.file.attribute.PosixFilePermissions.fromString(
                        java.util.Collections.singleton(java.nio.file.attribute.FileAttributeView.class.getName())));
                System.out.println("Set permissions: " + Integer.toOctalString(permissions));
            } else {
                throw new IOException("Failed to create file.");
            }
        }
    }
}