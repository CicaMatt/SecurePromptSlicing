import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermissions;

public class FilePermissionExample {
    public static void main(String[] args) {
        String filePath = "example.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter fileWriter = new FileWriter(filePath)) {
            fileWriter.write(content);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        Path path = Paths.get(filePath);

        try {
            Files.setPosixFilePermissions(path, PosixFilePermissions.fromString("rw-------"));
        } catch (IOException e) {
            System.err.println("Failed to set file permissions.");
            e.printStackTrace();
            return;
        }

        try {
            System.out.println("Current file permissions: " + Files.getPosixFilePermissions(path));
        } catch (IOException e) {
            System.err.println("Failed to get file permissions.");
            e.printStackTrace();
        }
    }
}