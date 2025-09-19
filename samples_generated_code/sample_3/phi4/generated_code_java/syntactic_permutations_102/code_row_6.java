import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class ConfigFileHandler {
    public static void main(String[] args) {
        String fileName = "important_config";
        String content = "important_config";

        try {
            // Check if the file exists
            boolean fileExists = Files.exists(Paths.get(fileName));
            
            // Open or create the file with the specified permissions
            FileOutputStream fos = new FileOutputStream(fileName, true);
            try {
                if (!fileExists) {
                    // Set read and write permissions for owner; read-only for others.
                    int mode = (S_IRUSR | S_IWUSR | S_IROTH);
                    Files.setPosixFilePermissions(Paths.get(fileName), java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--"));
                }
                
                // Write the content to the file
                fos.write(content.getBytes());
            } finally {
                fos.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static final int S_IRUSR = 0x00040000; // File is readable by owner.
    private static final int S_IWUSR = 0x00020000; // File is writable by owner.
    private static final int S_IROTH = 0x00000004; // File is readable by others.

}