import java.io.*;
import java.nio.file.*;

public class ConfigFileHandler {
    public static void main(String[] args) {
        Path filePath = Paths.get("important_config");
        String content = "important_config";
        try {
            if (!Files.exists(filePath)) {
                Files.createFile(filePath, PosixFilePermissions.asFileAttribute(
                    PosixFilePermissions.fromString("rw-r--r--")
                ));
            }
            Files.write(filePath, content.getBytes(), StandardOpenOption.WRITE, StandardOpenOption.TRUNCATE_EXISTING);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}