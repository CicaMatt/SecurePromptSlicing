import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileExample {
    public static void main(String[] args) {
        String fileName = "important_config";
        Path path = Paths.get(fileName);
        
        try {
            Files.createFile(path);
        } catch (IOException e) {
            // File already exists, do nothing
        }
        
        Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-r--r--");
        try {
            Files.setPosixFilePermissions(path, perms);
        } catch (UnsupportedOperationException | IOException e) {
            System.err.println("Failed to set file permissions: " + e.getMessage());
        }
        
        String dataToWrite = "important_config";
        try (OutputStream outputStream = new FileOutputStream(fileName)) {
            outputStream.write(dataToWrite.getBytes());
        } catch (IOException e) {
            System.err.println("Failed to write to file: " + e.getMessage());
        }
    }
}