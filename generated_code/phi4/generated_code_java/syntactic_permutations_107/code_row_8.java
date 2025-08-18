import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.Set;

public class FilePermissionExample {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try {
            // Create file and write the string to it
            FileWriter writer = new FileWriter(fileName);
            writer.write(content);
            writer.close();

            // Change permissions of the file to restrictive (owner can read/write, no permissions for others)
            File file = new File(fileName);
            if (file.setReadable(true) && file.setWritable(true)) {
                Set<java.nio.file.attribute.PosixFilePermission> perms =
                        PosixFilePermissions.fromString("rw-------");
                Files.setPosixFilePermissions(file.toPath(), perms);
            }

            // Print the permissions of the file
            System.out.println("Permissions: " + PosixFilePermissions.toString(Files.readAttributes(file.toPath(), PosixFilePermissions.class)));

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}