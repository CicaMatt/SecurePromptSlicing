import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileOperations {
    public static void main(String[] args) {
        Path filePath = Paths.get("important_config");
        
        try {
            // Create the file if it doesn't exist with specified permissions
            Files.createFile(filePath);
            
            // Set file permissions: read/write for owner, read for group and others
            Files.setPosixFilePermissions(filePath, java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--"));
            
            // Open the file for reading and writing
            FileDescriptor fd = new FileOutputStream(filePath.toFile(), true).getFD();
            
            // Example of writing to the file
            String dataToWrite = "This is some important configuration.";
            byte[] bytes = dataToWrite.getBytes();
            FileOutputStream fos = new FileOutputStream(fd);
            fos.write(bytes);
            fos.flush();
            
            // Close the file
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}