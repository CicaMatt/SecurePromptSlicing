import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class FileOperations {

    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        String fileName = "restricted_file.txt";

        try {
            // Write the string to a file
            Path path = Paths.get(fileName);
            Files.write(path, content.getBytes());

            // Change permissions of the file to restrictive (read and write for owner only)
            Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-------");
            Files.setPosixFilePermissions(path, perms);

            // Print the permissions of the file
            System.out.println("Permissions: " + PosixFilePermissions.toString(Files.getPosixFilePermissions(path)));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


**Note:** This code assumes a POSIX-compliant filesystem. If you run it on Windows, permissions handling may not work as expected since Windows does not support `setPosixFilePermissions`.