import java.io.FileWriter;
import java.io.IOException;

public class WriteToFile {
    public static void main(String[] args) {
        String content = "important_config";
        try (FileWriter writer = new FileWriter("important_config")) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}