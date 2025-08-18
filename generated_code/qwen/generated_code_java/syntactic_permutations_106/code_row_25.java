import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermissions;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info!";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        try {
            Files.setPosixFilePermissions(Paths.get(file.getPath()), PosixFilePermissions.fromString("r--------"));
        } catch (Exception e) {
            System.err.println("Failed to set file permissions.");
            e.printStackTrace();
        }

        try {
            String content = new String(Files.readAllBytes(Paths.get(file.getPath())));
            System.out.println(content);
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file.");
            e.printStackTrace();
        }
    }
}