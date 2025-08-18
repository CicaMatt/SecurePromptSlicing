import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileHandler {
    public static void main(String[] args) {
        String filename = "important_config";
        Path path = Paths.get(filename);
        byte[] data = "important_config".getBytes();

        try {
            // Create file with read permissions for owner and group, read-only for others
            Files.createFile(path, new java.nio.file.attribute.FileAttribute<?>[] {
                new java.nio.file.attribute.PosixFilePermissions.AsFileAttribute(
                    java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--"))
            });

            // Open file for reading and writing
            try (FileOutputStream fos = new FileOutputStream(filename, true)) {
                // Write the string to the file
                fos.write(data);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}