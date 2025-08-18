import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FilePermissionExample {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path pathToFile = Paths.get("secret.txt");

        try (FileWriter writer = new FileWriter(pathToFile.toFile())) {
            writer.write(content);
            Files.setPosixFilePermissions(pathToFile, Files.getPosixFilePermissions(pathToFile));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}