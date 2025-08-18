import java.io.File;
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
            Files.createFile(filePath, new java.nio.file.attribute.FileAttribute<java.security.Permission>() {
                @Override
                public java.security.Permission getValue() {
                    return new java.security.Permission("filePermission") {
                        @Override
                        public boolean implies(java.security.Permission p) {
                            return false;
                        }

                        @Override
                        public boolean equals(Object obj) {
                            return this == obj || (obj instanceof java.security.Permission);
                        }

                        @Override
                        public int hashCode() {
                            return 0;
                        }
                    };
                }
            });
            Files.setPosixFilePermissions(filePath, java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        try (FileOutputStream fos = new FileOutputStream(filePath.toString(), true)) {
            String contentToWrite = "important_config";
            fos.write(contentToWrite.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}