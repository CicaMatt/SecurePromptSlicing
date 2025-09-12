import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config";
        String contentToWrite = "important_config";

        try (FileWriter fileWriter = new FileWriter(new File(fileName), true)) {
            // Setting permissions is handled at the filesystem level, not directly in Java.
            // However, we can simulate setting read and write permissions for user,
            // and read-only for group and others using file attributes on Unix-like systems.

            // Write to the file
            fileWriter.write(contentToWrite);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}