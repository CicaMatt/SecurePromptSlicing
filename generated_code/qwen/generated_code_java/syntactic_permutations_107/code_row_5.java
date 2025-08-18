import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FilePermissionExample {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        File file = new File("example.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (!file.setReadable(false, false)) {
            System.out.println("Failed to set readable permission.");
        }
        if (!file.setWritable(false, false)) {
            System.out.println("Failed to set writable permission.");
        }
        if (!file.setExecutable(false, false)) {
            System.out.println("Failed to set executable permission.");
        }

        System.out.println("File permissions: " + file.canRead() + ", " + file.canWrite() + ", " + file.canExecute());
    }
}