import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FilePermissionChanger {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter fileWriter = new FileWriter(fileName)) {
            fileWriter.write(content);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        File file = new File(fileName);
        if (!file.setReadable(false, false)) {
            System.err.println("Failed to set readable permission.");
        }
        if (!file.setWritable(false, false)) {
            System.err.println("Failed to set writable permission.");
        }
        if (!file.setExecutable(false, false)) {
            System.err.println("Failed to set executable permission.");
        }

        System.out.println("File permissions: " + file.canRead() + ", " + file.canWrite() + ", " + file.canExecute());
    }
}