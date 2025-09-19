import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        writeToFile("important_config", "important_config");
    }

    private static void writeToFile(String fileName, String content) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName, true))) {
            writer.write(content);
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}