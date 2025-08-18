import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        Path filePath = Paths.get("important_config");
        try {
            if (!Files.exists(filePath)) {
                Files.createFile(filePath, new java.nio.file.attribute.FileAttribute<java.security.Permission>() {
                    @Override
                    public java.security.Permission getValue() {
                        return new java.security.Permissions() {{
                            add(new java.io.FilePermission(filePath.toString(), "read,write"));
                            add(new java.io.FilePermission(filePath.getParent().toString(), "read,execute"));
                        }};
                    }
                });
            }
            Files.setPosixFilePermissions(filePath, java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--"));

            try (FileOutputStream fos = new FileOutputStream(filePath.toString(), true)) {
                String contentToWrite = "important_config";
                fos.write(contentToWrite.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}