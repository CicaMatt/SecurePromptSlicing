import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class ConfigWriter {
    public static void main(String[] args) {
        File config = new File("important_config");
        try (FileWriter writer = new FileWriter(config, false)) {
            // The file is now open with write permissions
            // Here you can write to the file using writer.write("data")
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}