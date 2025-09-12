import java.io.FileWriter;
import java.io.IOException;

public class WriteToFile {
    public static void main(String[] args) {
        String fileName = "important_config";
        String contentToWrite = "important_config";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(contentToWrite);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }
    }
}