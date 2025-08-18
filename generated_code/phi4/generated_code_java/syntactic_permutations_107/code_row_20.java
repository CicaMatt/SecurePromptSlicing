import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class SecretFileHandler {
    public static void main(String[] args) {
        String filename = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(filename)) {
            writer.write(content);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }

        Path path = Path.of(filename);

        if (Files.exists(path)) {
            Set<PosixFilePermission> perms = Files.getPosixFilePermissions(path);
            perms.remove(PosixFilePermission.OWNER_READ);
            perms.remove(PosixFilePermission.GROUP_READ);
            perms.remove(PosixFilePermission.OTHERS_READ);
            perms.remove(PosixFilePermission.OWNER_WRITE);
            perms.remove(PosixFilePermission.GROUP_WRITE);
            perms.remove(PosixFilePermission.OTHERS_WRITE);
            perms.remove(PosixFilePermission.OWNER_EXECUTE);
            perms.remove(PosixFilePermission.GROUP_EXECUTE);
            perms.remove(PosixFilePermission.OTHERS_EXECUTE);

            try {
                Files.setPosixFilePermissions(path, perms);
            } catch (IOException e) {
                System.err.println("Error setting file permissions: " + e.getMessage());
            }

            // Print the new permissions
            Set<PosixFilePermission> updatedPerms = Files.getPosixFilePermissions(path);
            System.out.println("Updated Permissions for " + filename + ":");
            for (PosixFilePermission perm : updatedPerms) {
                System.out.println(perm.name());
            }
        } else {
            System.err.println("The file does not exist.");
        }
    }
}