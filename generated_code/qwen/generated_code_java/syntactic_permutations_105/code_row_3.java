import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(filePath)) {
            writer.write(content);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        File file = new File(filePath);
        if (!file.setReadable(false, false) || !file.setWritable(false, false) || !file.setExecutable(false, false)) {
            System.err.println("Failed to set restrictive permissions for the file.");
        }
    }
}