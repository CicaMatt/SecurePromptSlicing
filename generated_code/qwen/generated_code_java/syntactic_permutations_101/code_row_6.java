import java.io.FileWriter;
import java.io.IOException;

public class WriteToFile {
    public static void main(String[] args) {
        String fileName = "config.txt";
        String contentToWrite = "important_config";

        try (FileWriter fileWriter = new FileWriter(fileName)) {
            fileWriter.write(contentToWrite);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}