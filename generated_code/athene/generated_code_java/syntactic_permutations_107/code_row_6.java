import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FilePermissionsExample {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        String fileName = "secret.txt";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(content);
            Path path = Paths.get(fileName);
            Files.setPosixFilePermissions(path, java.nio.file.attribute.PosixFilePermissions.fromString("rw-------"));
            System.out.println(Files.getPosixFilePermissions(path));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}