import java.nio.file.*;
import java.io.*;

public class FileCreator {
    public static void main(String[] args) throws Exception {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path path = Paths.get("secret.txt");
        Files.write(path, content.getBytes(), StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING);
        
        if (System.getProperty("os.name").toLowerCase().contains("windows")) {
            // Windows does not support the same permission model as Unix
            return;
        }
        
        Set<PosixFilePermission> perms = new HashSet<>();
        perms.add(PosixFilePermission.OWNER_READ);
        perms.add(PosixFilePermission.OWNER_WRITE);
        Files.setPosixFilePermissions(path, perms);
    }
}