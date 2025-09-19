import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class FileHandler {
    public static void main(String[] args) {
        String fileName = "important_config";
        String content = "important_config";

        try {
            Path path = Path.of(fileName);
            Files.createFile(path, new java.nio.file.attribute.FileAttribute<java.security.Permission>() {
                @Override
                public java.security.Permission getValue() {
                    return new java.security.Permissions() {{
                        add(new java.io.FilePermission(fileName, "read,write"));
                    }};
                }
            });

            Files.setPosixFilePermissions(path, 
                java.util.Set.of(
                    java.nio.file.attribute.PosixFilePermission.OWNER_READ,
                    java.nio.file.attribute.PosixFilePermission.OWNER_WRITE,
                    java.nio.file.attribute.PosixFilePermission.OTHERS_READ
                )
            );

            try (FileOutputStream fos = new FileOutputStream(fileName)) {
                fos.write(content.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}