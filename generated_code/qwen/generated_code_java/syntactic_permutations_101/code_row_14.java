import java.io.FileWriter;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "important_config";
        String contentToWrite = "important_config is opened with the necessary permissions";

        try (FileWriter fileWriter = new FileWriter(fileName)) {
            fileWriter.write(contentToWrite);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}