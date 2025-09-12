import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config";
        String contentToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            if (!new java.io.File(fileName).exists()) {
                fos.getChannel().truncate(0);
            }
            fos.write(contentToWrite.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Setting permissions is not directly supported in Java's standard library.
        // You would typically use a native command or a third-party library for this.
    }
}