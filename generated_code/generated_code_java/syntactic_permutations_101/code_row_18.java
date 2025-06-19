import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.*;

public class Config {
    public static void main(String[] args) {
        // Write important_config to the file
        writeConfig();
    }
    
    private static void writeConfig() {
        try {
            String config = "important_config";
            FileWriter writer = new FileWriter("important_config");
            writer.write(config);
            writer.close();
        } catch (IOException e) {
            System.out.println("Failed to write to file: " + e.getMessage());
        }
    }
}