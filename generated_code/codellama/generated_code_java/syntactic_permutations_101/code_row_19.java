import java.io.FileWriter;
import java.io.IOException;

public class ImportantConfig {
    public static void main(String[] args) {
        try (FileWriter writer = new FileWriter("important_config")) {
            writer.write("important_config");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}