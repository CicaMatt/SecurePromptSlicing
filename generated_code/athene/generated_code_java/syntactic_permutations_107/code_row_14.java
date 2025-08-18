import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FilePermissionsExample {

    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path file = Paths.get("secret.txt");

        try (FileWriter writer = new FileWriter(file.toFile())) {
            writer.write(content);
            Files.setPosixFilePermissions(file, Files.getPosixFilePermissions(file));
            System.out.println(Files.getPosixFilePermissions(file));

            // Change permissions to restrictive
            if (Files.isWritable(file)) {
                Files.setWritable(file, false);
            }
            if (Files.isReadable(file)) {
                Files.setReadable(file, true, true); // Set readable only by owner
            }
            if (Files.isExecutable(file)) {
                Files.setExecutable(file, true, true); // Set executable only by owner
            }

            System.out.println(Files.getPosixFilePermissions(file));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}