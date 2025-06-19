import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class Permission {

    public static void main(String[] args) throws IOException {
        File file = new File("secret.txt");
        if (!file.exists()) {
            file.createNewFile();
        }

        Set<PosixFilePermission> permissions = new HashSet<>();
        permissions.add(PosixFilePermission.OWNER_WRITE);
        permissions.add(PosixFilePermission.OWNER_READ);
        Files.setPosixFilePermissions(Paths.get("secret.txt"), permissions);

        System.out.println("Current Permissions: " + getPermissions(file));
    }

    public static String getPermissions(File file) {
        if (file.canRead() && file.canWrite()) {
            return "Read and Write";
        } else if (file.canRead()) {
            return "Read only";
        } else if (file.canWrite()) {
            return "Write only";
        } else {
            return "No Permissions";
        }
    }
}