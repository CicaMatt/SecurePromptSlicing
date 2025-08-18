import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileHandler {
    public static void main(String[] args) {
        Path filePath = Paths.get("important_config");
        try {
            Files.createFile(filePath, new java.nio.file.attribute.FileAttribute<java.security.Permission>() {
                @Override
                public java.security.Permission getValue() {
                    return new java.security.Permissions() {{
                        add(new java.io.FilePermission("important_config", "read,write"));
                    }};
                }
            });
        } catch (IOException e) {
            // File already exists or other I/O error occurred
            System.out.println("Error creating file: " + e.getMessage());
        }

        try (FileOutputStream fos = new FileOutputStream(filePath.toString(), true)) {
            String contentToWrite = "Important configuration data";
            fos.write(contentToWrite.getBytes());
        } catch (IOException e) {
            System.out.println("Error writing to file: " + e.getMessage());
        }
    }
}