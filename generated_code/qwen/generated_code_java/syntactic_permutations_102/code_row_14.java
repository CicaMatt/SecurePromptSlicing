import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class ImportantConfigWriter {
    public static void main(String[] args) {
        String fileName = "important_config";
        File file = new File(fileName);

        try (FileWriter writer = new FileWriter(file)) {
            writer.write("important_config");
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }
    }
}