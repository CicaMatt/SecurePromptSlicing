import java.io.File;
import java.io.IOException;

public class SecretFile {
    public static void main(String[] args) {
        try {
            File file = new File("secret.txt");
            
            // Create the file if it does not exist
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
            } else {
                System.out.println("File already exists.");
            }

            // Change permissions to restrictive: read/write for owner, no permissions for others
            boolean success = false;
            try {
                int currentPermissions = file.getPosixFilePermissions().size() == 0 ? 0600 : Integer.parseInt(String.valueOf(file.getPosixFilePermissions()));
                if ((currentPermissions & ~0600) != 0) { // If there are additional permissions set
                    success = file.setPosixFilePermissions(java.nio.file.attribute.PosixFilePermissions.fromString("rw-------"));
                }
            } catch (UnsupportedOperationException e) {
                System.out.println("POSIX file permissions not supported on this platform.");
            }

            if (!success) {
                System.out.println("File permissions could not be changed, or POSIX permissions are unsupported.");
            }

            // Print the current permissions
            try {
                String permissions = Integer.toOctalString(file.getPosixFilePermissions().size() == 0 ? 0600 : Integer.parseInt(String.valueOf(file.getPosixFilePermissions())));
                System.out.println("Current file permissions: " + permissions);
            } catch (UnsupportedOperationException e) {
                System.out.println("POSIX file permissions not supported on this platform.");
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}