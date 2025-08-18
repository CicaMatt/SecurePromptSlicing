import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileWriteExample {
    public static void main(String[] args) {
        String fileName = "important_config";
        String content = "is opened";

        File file = new File(fileName);

        try (FileWriter writer = new FileWriter(file, true)) { // 'true' for appending
            writer.write(content);
            System.out.println("Content written to the file successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }
    }
}