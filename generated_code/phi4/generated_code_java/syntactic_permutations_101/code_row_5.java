import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class WriteToFile {

    public static void main(String[] args) {
        String filePath = "config.txt";
        String content = "important_config";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath, true))) {
            writer.write(content);
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}