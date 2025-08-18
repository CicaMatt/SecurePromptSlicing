import java.io.*;
import java.nio.file.*;
import java.nio.file.attribute.*;

public class FileOpener {
    public static void main(String[] args) {
        Path path = Paths.get("important_config");
        try {
            if (!Files.exists(path)) {
                Files.createFile(path);
                Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-r--r--");
                Files.setPosixFilePermissions(path, perms);
            }

            String contentToWrite = "This is a test.";
            Files.write(path, contentToWrite.getBytes(), StandardOpenOption.CREATE, StandardOpenOption.APPEND);

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}