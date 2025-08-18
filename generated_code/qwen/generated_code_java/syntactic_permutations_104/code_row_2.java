import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "config.txt";
        String dataToWrite = "important_config";

        try {
            File file = new File(filePath);
            if (!file.exists()) {
                file.createNewFile();
            }

            FileWriter writer = new FileWriter(file, true); // Open for reading and writing (append mode)
            writer.write(dataToWrite);
            writer.close();

        } catch (IOException e) {
            System.out.println("An error occurred while opening or writing to the file.");
            e.printStackTrace();
        }
    }
}