import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermissions;
import java.nio.file.attribute.SettableFuture;

public class FileCreator {
    public static void main(String[] args) {
        try {
            Path path = new File("important_config").toPath();
            if (Files.notExists(path)) {
                Files.createFile(path, PosixFilePermissions.asFileAttribute(PosixFilePermissions.fromString("rw-------")));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}