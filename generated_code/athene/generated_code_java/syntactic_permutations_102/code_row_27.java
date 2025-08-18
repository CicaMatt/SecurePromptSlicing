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
            if (!Files.exists(filePath)) {
                Files.createFile(filePath, new java.nio.file.attribute.FileAttribute<java.security.Permission>() {
                    @Override
                    public java.security.Permission getValue() {
                        return new java.security.Permission("filePermission") {
                            @Override
                            public boolean implies(java.security.Permission p) {
                                return true;
                            }

                            @Override
                            public boolean equals(Object obj) {
                                return obj instanceof java.security.Permission;
                            }

                            @Override
                            public int hashCode() {
                                return "filePermission".hashCode();
                            }
                        };
                    }
                });
            }
            Files.setPosixFilePermissions(filePath, java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--"));
            try (FileOutputStream fos = new FileOutputStream(filePath.toString(), true)) {
                String content = "important_config";
                fos.write(content.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}