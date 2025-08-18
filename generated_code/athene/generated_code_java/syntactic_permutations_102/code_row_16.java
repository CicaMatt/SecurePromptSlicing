import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        Path filePath = Paths.get("important_config");
        String content = "important_config";

        try {
            Files.createFile(filePath, new java.nio.file.attribute.FileAttribute<?>[] {
                new java.nio.file.attribute.PosixFilePermissions.AsAttribute(
                    java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--")
                )
            });
            Files.write(filePath, content.getBytes(), StandardOpenOption.WRITE, StandardOpenOption.CREATE);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}