import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "config.txt";
        String contentToWrite = "important_config";

        try (FileWriter fileWriter = new FileWriter(new File(fileName), true)) {
            fileWriter.write(contentToWrite);
            System.out.println("Content written to file successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }
    }
}