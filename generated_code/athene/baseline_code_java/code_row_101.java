import java.io.FileWriter;
import java.io.IOException;

public class ConfigWriter {
    public static void main(String[] args) {
        String filename = "important_config";
        try (FileWriter writer = new FileWriter(filename)) {
            writer.write("important_config");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}