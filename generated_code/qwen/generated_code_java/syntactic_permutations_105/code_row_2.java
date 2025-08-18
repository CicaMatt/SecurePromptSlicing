import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileOutputStream fos = new FileOutputStream(filePath)) {
            fos.write(content.getBytes());
            fos.close();
            java.nio.file.Files.setPosixFilePermissions(
                java.nio.file.Paths.get(filePath),
                java.util.Set.of(java.nio.file.attribute.PosixFilePermission.OWNER_READ)
            );
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}