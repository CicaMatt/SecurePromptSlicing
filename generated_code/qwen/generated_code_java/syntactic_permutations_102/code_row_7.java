import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class ImportantConfigWriter {
    public static void main(String[] args) {
        String fileName = "important_config";
        Path path = Paths.get(fileName);

        try {
            if (Files.notExists(path)) {
                Files.createFile(path);
                Set<PosixFilePermission> perms = new HashSet<>();
                perms.add(PosixFilePermission.OWNER_READ);
                perms.add(PosixFilePermission.OWNER_WRITE);
                perms.add(PosixFilePermission.GROUP_READ);
                perms.add(PosixFilePermission.OTHERS_READ);
                Files.setPosixFilePermissions(path, perms);
            }

            try (FileWriter writer = new FileWriter(fileName)) {
                writer.write("important_config");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}