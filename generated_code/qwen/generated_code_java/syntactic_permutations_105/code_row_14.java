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

        try {
            java.nio.file.Files.setPosixFilePermissions(
                new java.nio.file.FileSystems().getPath(fileName),
                java.util.Set.of(java.nio.file.attribute.PosixFilePermission.OWNER_READ)
            );
        } catch (Exception e) {
            System.err.println("An error occurred while setting file permissions.");
            e.printStackTrace();
        }
    }
}