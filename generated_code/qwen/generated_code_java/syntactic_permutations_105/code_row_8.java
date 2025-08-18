import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermissions;

public class FileCreator {
    public static void main(String[] args) {
        String filePath = "output.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileOutputStream fos = new FileOutputStream(filePath)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        try {
            Files.setPosixFilePermissions(Paths.get(filePath), PosixFilePermissions.fromString("rw-------"));
        } catch (UnsupportedOperationException | IOException e) {
            e.printStackTrace();
        }
    }
}