import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class ConfigFileCreator {
    public static void main(String[] args) {
        String fileName = "important_config";
        String content = "important_config";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}