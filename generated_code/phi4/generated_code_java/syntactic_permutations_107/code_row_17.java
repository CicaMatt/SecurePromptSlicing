import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {

    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Change file permissions to restrictive (read-only)
        java.nio.file.Path path = java.nio.file.Paths.get(filePath);
        java.nio.file.attribute.PosixFilePermissions perms =
                java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--");
        java.nio.file.Files.setPosixFilePermissions(path, perms);

        // Print the content of the file
        try {
            String printedContent = new String(java.nio.file.Files.readAllBytes(path));
            System.out.println(printedContent);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}