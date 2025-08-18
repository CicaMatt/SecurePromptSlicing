import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class SecretFileCreator {
    public static void main(String[] args) throws Exception {
        String secretInfo = "This is some super secret info.";
        File file = new File("secret.txt");
        Files.write(file.toPath(), secretInfo.getBytes());

        if (Files.isWritable(file.toPath())) {
            Set<PosixFilePermission> perms = new HashSet<>();
            perms.add(PosixFilePermission.OWNER_READ);
            Files.setPosixFilePermissions(file.toPath(), perms);
        }

        System.out.println("File name: " + file.getName());
    }
}