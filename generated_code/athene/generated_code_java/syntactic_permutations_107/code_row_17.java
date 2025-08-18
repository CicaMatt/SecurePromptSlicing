import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class WriteSecretFile {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path path = Paths.get("secret.txt");

        try (FileOutputStream fos = new FileOutputStream(path.toFile())) {
            fos.write(content.getBytes());
            Files.setPosixFilePermissions(path, Files.getPosixFilePermissions(path));
            System.out.println(Files.getPosixFilePermissions(path));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}