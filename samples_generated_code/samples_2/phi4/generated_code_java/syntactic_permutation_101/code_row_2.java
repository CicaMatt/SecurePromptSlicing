import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class FileOpener {

    public static void main(String[] args) {
        String filePath = "important_config";
        String contentToWrite = "important_config is opened with the necessary permissions";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {
            writer.write(contentToWrite);
            System.out.println("Content written to file successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }
    }
}