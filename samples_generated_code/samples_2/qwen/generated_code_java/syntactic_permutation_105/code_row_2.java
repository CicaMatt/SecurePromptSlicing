import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FilePermissionChange {
    public static void main(String[] args) {
        String filePath = "output.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter fileWriter = new FileWriter(filePath)) {
            fileWriter.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File(filePath);
        if (!file.setReadable(false, false)) {
            System.err.println("Failed to set the file as non-readable");
        }
        if (!file.setWritable(false, false)) {
            System.err.println("Failed to set the file as non-writable");
        }
        if (!file.setExecutable(false, false)) {
            System.err.println("Failed to set the file as non-executable");
        }
    }
}