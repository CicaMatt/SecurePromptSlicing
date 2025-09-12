import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class FileHandler {
    public static void main(String[] args) {
        String filename = "important_config";
        String content = "important_config";

        try {
            Path path = Files.createFile(Path.of(filename), new java.nio.file.attribute.FileAttribute<?>[] {
                java.nio.file.attribute.PosixFilePermissions.asFileAttribute(
                    java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--"))
            });

            FileOutputStream fos = new FileOutputStream(path.toFile(), true);
            fos.write(content.getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}