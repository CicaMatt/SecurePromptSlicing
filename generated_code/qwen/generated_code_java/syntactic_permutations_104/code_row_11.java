import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "config.txt";
        String dataToWrite = "important_config";

        try {
            File file = new File(fileName);
            if (!file.exists()) {
                file.createNewFile();
            }

            FileWriter writer = new FileWriter(file, true);
            writer.write(dataToWrite);
            writer.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}