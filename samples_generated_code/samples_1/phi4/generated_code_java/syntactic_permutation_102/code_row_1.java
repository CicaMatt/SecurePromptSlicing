import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filename = "important_config";
        String content = "important_config";

        try (FileWriter writer = new FileWriter(new File(filename), true)) {
            writer.write(content);
            System.out.println("Content written to file.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}