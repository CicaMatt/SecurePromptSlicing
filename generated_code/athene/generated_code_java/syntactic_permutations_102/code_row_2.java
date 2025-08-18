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


Note: Java does not have a direct equivalent to the C `open` function with flags like `O_CREAT`, `S_IRUSR`, etc. The closest approximation is using `Files.createFile` and setting permissions through `setPosixFilePermissions`. However, due to limitations in Java's security model and cross-platform considerations, the above code uses `FilePermission` which does not fully replicate the Unix permission model but provides a similar functionality. For a more precise implementation of Unix-like permissions, you would need to use JNI or a third-party library like Apache Commons IO.