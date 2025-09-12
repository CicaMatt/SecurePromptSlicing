import java.io.FileWriter;
import java.io.IOException;

public class ConfigFileHandler {
    public static void main(String[] args) {
        String fileName = "important_config";
        String content = "important_config";

        try (FileWriter fileWriter = new FileWriter(fileName, true)) {
            fileWriter.write(content + System.lineSeparator());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}