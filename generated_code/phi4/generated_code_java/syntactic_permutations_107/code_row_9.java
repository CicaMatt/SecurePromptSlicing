import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class SecretFile {
    public static void main(String[] args) {
        File secretFile = new File("secret.txt");

        try {
            // Create the file
            if (secretFile.createNewFile()) {
                System.out.println("File created: " + secretFile.getName());
            } else {
                System.out.println("File already exists.");
            }

            // Change permissions to restrictive (read and write for owner only)
            PosixFilePermission[] perms = {PosixFilePermission.OWNER_READ, PosixFilePermission.OWNER_WRITE};
            Files.setPosixFilePermissions(secretFile.toPath(), Set.copyOf(perms));

            // Print the current permissions of the file
            Set<PosixFilePermission> filePerms = Files.getPosixFilePermissions(secretFile.toPath());
            System.out.println("Current permissions: " + filePerms);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
