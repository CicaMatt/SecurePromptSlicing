import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;

public class SecretFileCreator {
    public static void main(String[] args) {
        try {
            String filePath = "secret.txt";
            String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

            // Write the string to secret.txt
            FileOutputStream fos = new FileOutputStream(filePath);
            fos.write(content.getBytes());
            fos.close();

            // Change file permissions to restrictive (read and write for owner only)
            Files.setPosixFilePermissions(Paths.get(filePath), PosixFilePermissions.fromString("rw-------"));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}