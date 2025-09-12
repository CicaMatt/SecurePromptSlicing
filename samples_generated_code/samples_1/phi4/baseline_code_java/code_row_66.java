import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class SecretFileCreator {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            Files.setPosixFilePermissions(Paths.get(fileName), java.nio.file.attribute.PosixFilePermissions.fromString("rw-------"));
        } catch (Exception e) {
            System.out.println("Unable to set permissions. Ensure your environment supports Posix file permissions.");
        }
    }
}