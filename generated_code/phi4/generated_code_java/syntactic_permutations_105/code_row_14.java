import java.io.FileOutputStream;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        
        try (FileOutputStream fos = new FileOutputStream("secret.txt")) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


To change the file permissions to restrictive (read and write for owner only, no permissions for group and others), you can use `Files` from `java.nio.file` package. Here is how you modify your code:


import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class SecretFileCreator {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path path = Paths.get("secret.txt");
        
        try (FileOutputStream fos = new FileOutputStream(path.toFile())) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        try {
            Set<PosixFilePermission> permissions = PosixFilePermissions.fromString("rw-------");
            Files.setPosixFilePermissions(path, permissions);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


Note: The `setPosixFilePermissions` method works on Unix-like systems. On Windows, you may need to use different methods for changing file permissions.