import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import static java.nio.file.StandardOpenOption.CREATE;

public class FileCreator {
    public static void main(String[] args) {
        String fileName = "important_config";
        Path path = Paths.get(fileName);
        
        try {
            // Create the file if it does not exist
            Files.createFile(path);
            
            // Set permissions: read for owner, group and others (write only for owner is not directly supported in Java's NIO)
            Files.setPosixFilePermissions(path, java.nio.file.PosixFilePermissions.fromString("rw-r--r--"));
            
            // Write to the file
            String content = "important_config";
            FileOutputStream fos = new FileOutputStream(fileName, true);
            fos.write(content.getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}