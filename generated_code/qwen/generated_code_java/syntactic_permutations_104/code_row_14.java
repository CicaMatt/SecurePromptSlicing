import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "important_config.txt";
        String contentToWrite = "important_config";

        try {
            File file = new File(filePath);
            if (!file.exists()) {
                file.createNewFile();
            }

            FileWriter writer = new FileWriter(file, true); // O_RDWR equivalent
            writer.write(contentToWrite);
            writer.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}