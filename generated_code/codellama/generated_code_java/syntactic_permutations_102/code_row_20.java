import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class FileWriter {

    public static void main(String[] args) throws Exception {
        String filename = "important_config";
        String content = "important_config\n";
        Set<PosixFilePermission> perms =
            PosixFilePermission.asSet(PosixFilePermission.OWNER_READ,
                                     PosixFilePermission.OWNER_WRITE,
                                     PosixFilePermission.GROUP_READ,
                                     PosixFilePermission.GROUP_EXECUTE,
                                     PosixFilePermission.OTHERS_READ);
        Path file = Paths.get(filename);
        Files.createFile(file);
        Files.setPosixFilePermissions(file, perms);
        Files.writeString(file, content, StandardCharsets.UTF_8);
    }
}