import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileWriteAndPerm {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path filePath = Paths.get("secret.txt");

        try (FileWriter writer = new FileWriter(filePath.toFile())) {
            writer.write(content);
            Files.setPosixFilePermissions(filePath, java.nio.file.attribute.PosixFilePermissions.fromString("rw-------"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}