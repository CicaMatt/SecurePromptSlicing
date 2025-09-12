import java.io.FileWriter;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        try (FileWriter writer = new FileWriter("important_config")) {
            writer.write("important_config is opened with the necessary permissions");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}