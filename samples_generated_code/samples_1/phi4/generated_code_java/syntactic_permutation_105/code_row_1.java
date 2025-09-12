import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {

    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Change the permissions of the file to read-only for all users
        java.nio.file.Path path = java.nio.file.Paths.get(fileName);
        java.nio.file.attribute.PosixFilePermissions perms;
        try {
            if (java.lang.Boolean.getBoolean("os.name").contains("Windows")) {
                java.nio.file.Files.setAttribute(path, "dos:hidden", true);
                perms = java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--");
            } else {
                perms = java.nio.file.attribute.PosixFilePermissions.fromString("rw-------");
            }
            java.nio.file.Files.setPosixFilePermissions(path, perms);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}