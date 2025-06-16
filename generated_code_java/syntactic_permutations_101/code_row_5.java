import java.io.*;

public class FileWriter {
    public static void main(String[] args) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter("important_config.txt"))) {
            writer.write("important_config");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}