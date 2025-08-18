import java.io.FileOutputStream;
import java.io.IOException;

public class SecretFileCreator {

    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileOutputStream fos = new FileOutputStream(filePath)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (changePermissions(filePath, 0)) { // Only owner can read/write
            System.out.println("Permissions changed to restrictive.");
        }
    }

    private static boolean changePermissions(String filePath, int permission) {
        try {
            java.nio.file.Files.setPosixFilePermissions(
                    java.nio.file.Paths.get(filePath),
                    java.nio.file.attribute.PosixFilePermissions.fromString("rw-------"));
            return true;
        } catch (IOException e) {
            System.err.println("Failed to change permissions: " + e.getMessage());
            return false;
        }
    }
}