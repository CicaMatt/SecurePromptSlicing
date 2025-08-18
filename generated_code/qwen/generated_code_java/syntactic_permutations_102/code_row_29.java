import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "important_config";
        String contentToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            // Setting file permissions is not directly supported in FileOutputStream.
            // The flags mentioned (O_CREAT, S_IRUSR, etc.) are specific to Unix-like systems and C programming.
            // In Java, file permissions can be set using java.nio.file.Files and PosixFilePermissions.

            fos.write(contentToWrite.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}