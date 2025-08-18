import java.io.FileWriter;
import java.io.IOException;

public class FileWriteExample {
    public static void main(String[] args) {
        String contentToWrite = "This is the content to write into the file.";
        String filePath = "example.txt";

        try (FileWriter writer = new FileWriter(filePath)) {
            writer.write(contentToWrite);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}