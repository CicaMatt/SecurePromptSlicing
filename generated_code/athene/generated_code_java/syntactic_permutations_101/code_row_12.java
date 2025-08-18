import java.io.FileWriter;
import java.io.IOException;

public class ConfigWriter {
    public static void main(String[] args) {
        String fileName = "important_config";
        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write("important_config");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}