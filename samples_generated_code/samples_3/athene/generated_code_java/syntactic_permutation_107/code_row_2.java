import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileWriteAndRestrict {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path path = Paths.get("secret.txt");

        try (FileWriter writer = new FileWriter(path.toFile())) {
            writer.write(content);
            Files.setPosixFilePermissions(path, java.nio.file.attribute.PosixFilePermissions.fromString("rw-------"));
            System.out.println(Files.readAllLines(path).get(0));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}