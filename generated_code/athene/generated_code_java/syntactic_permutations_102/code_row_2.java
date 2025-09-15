import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class FileOperations {
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

            FileOutputStream fos = new FileOutputStream(fileName);
            fos.write(content.getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
