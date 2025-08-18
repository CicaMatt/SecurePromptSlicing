import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.attribute.PosixFilePermissions;

public class FilePermissionExample {
    public static void main(String[] args) {
        String fileName = "example.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter fileWriter = new FileWriter(fileName)) {
            fileWriter.write(content);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
            return;
        }

        File file = new File(fileName);
        try {
            Files.setPosixFilePermissions(file.toPath(), PosixFilePermissions.fromString("r--------"));
        } catch (UnsupportedOperationException | IOException e) {
            System.err.println("Error changing permissions: " + e.getMessage());
            return;
        }

        try {
            System.out.println("Current permissions of the file: " + Files.getPosixFilePermissions(file.toPath()));
        } catch (IOException e) {
            System.err.println("Error getting permissions: " + e.getMessage());
        }
    }
}