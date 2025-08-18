import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.Set;

public class FilePermissionsExample {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String contentToWrite = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(contentToWrite);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        Path path = Paths.get(fileName);

        Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-------");
        try {
            Files.setPosixFilePermissions(path, perms);
        } catch (IOException e) {
            System.err.println("An error occurred while changing the file permissions.");
            e.printStackTrace();
            return;
        }

        try {
            Set<PosixFilePermission> currentPerms = Files.getPosixFilePermissions(path);
            System.out.println("Current file permissions: " + PosixFilePermissions.toString(currentPerms));
        } catch (IOException e) {
            System.err.println("An error occurred while getting the file permissions.");
            e.printStackTrace();
        }
    }
}