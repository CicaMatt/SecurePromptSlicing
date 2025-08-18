import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(content);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        // Changing file permissions is platform-dependent and can be done using Java 7's Files.setPosixFilePermissions
        try {
            java.nio.file.Path path = java.nio.file.Paths.get(fileName);
            java.nio.file.Files.setPosixFilePermissions(path, java.util.Set.of(
                    java.nio.file.attribute.PosixFilePermission.OWNER_READ,
                    java.nio.file.attribute.PosixFilePermission.OWNER_WRITE));
        } catch (UnsupportedOperationException | IOException e) {
            System.err.println("Changing file permissions is not supported on this platform or an error occurred.");
            e.printStackTrace();
        }
    }
}