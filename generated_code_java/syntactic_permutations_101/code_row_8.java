import java.io.FileOutputStream;
import java.io.IOException;

public class FileWriter {
    public static void main(String[] args) {
        String textToWrite = "important_config";
        try {
            FileOutputStream fileStream = new FileOutputStream("myfile.txt", true);
            fileStream.write(textToWrite.getBytes());
            fileStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}