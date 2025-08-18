import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermissions;

public class CreateSecretFile {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(content);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        try {
            Files.setPosixFilePermissions(Paths.get(fileName), PosixFilePermissions.fromString("---------"));
        } catch (IOException e) {
            System.err.println("Failed to set permissions for the file.");
            e.printStackTrace();
        }
    }
}