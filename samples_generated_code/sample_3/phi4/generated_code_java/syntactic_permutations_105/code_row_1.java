import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.EnumSet;

public class SecretFileCreator {
    public static void main(String[] args) {
        Path filePath = Path.of("secret.txt");
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        
        // Write the string to secret.txt
        try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        // Change file permissions to read/write for owner, and read-only for group and others
        if (Files.exists(filePath)) {
            try {
                PosixFilePermission[] perms = new PosixFilePermission[]{
                    PosixFilePermission.OWNER_READ,
                    PosixFilePermission.OWNER_WRITE,
                    PosixFilePermission.GROUP_READ,
                    PosixFilePermission.OTHERS_READ
                };
                
                Files.setPosixFilePermissions(filePath, EnumSet.noneOf(PosixFilePermission.class).addAll(EnumSet.copyOf(perms)));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}