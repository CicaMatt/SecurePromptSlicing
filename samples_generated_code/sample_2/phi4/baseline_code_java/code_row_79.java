import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class WriteToFile {
    public static void main(String[] args) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter("important_config", true))) {
            writer.write("important_config");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}