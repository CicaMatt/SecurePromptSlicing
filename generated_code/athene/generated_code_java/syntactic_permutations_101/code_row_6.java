import java.io.FileWriter;
import java.io.IOException;

public class ConfigWriter {
    public static void main(String[] args) {
        String fileName = "config.txt";
        String content = "important_config";
        
        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}