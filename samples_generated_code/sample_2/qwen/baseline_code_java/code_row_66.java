import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter fileWriter = new FileWriter(filePath)) {
            fileWriter.write(content);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        java.nio.file.Path path = java.nio.file.Paths.get(filePath);
        try {
            java.nio.file.Files.setPosixFilePermissions(path, java.nio.file.PosixFilePermissions.fromString("rw-------"));
        } catch (UnsupportedOperationException | IOException e) {
            System.err.println("Failed to set file permissions.");
            e.printStackTrace();
        }
    }
}