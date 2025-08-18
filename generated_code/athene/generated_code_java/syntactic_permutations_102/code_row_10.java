import java.io.File;
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
        
        try {
            if (!Files.exists(path)) {
                Files.createFile(path, new java.nio.file.attribute.FileAttribute<java.security.Permission>() {
                    @Override
                    public java.security.Permission getValue() {
                        return new java.security.Permissions() {{
                            add(new java.io.FilePermission(filename, "read,write"));
                            add(new java.io.FilePermission(filename, "read"));
                        }};
                    }
                });
            }

            Files.setPosixFilePermissions(path, 
                java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--"));

            try (FileOutputStream fos = new FileOutputStream(filename)) {
                String content = "important_config";
                fos.write(content.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}