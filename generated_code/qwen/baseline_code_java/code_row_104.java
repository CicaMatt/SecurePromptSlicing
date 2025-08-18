import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "config.txt";
        String contentToWrite = "important_config";

        try {
            // O_CREAT: Create the file if it does not exist
            File file = new File(fileName);
            if (!file.exists()) {
                file.createNewFile();
            }

            // O_RDWR: Open for reading and writing, here we are just showing writing part
            FileWriter writer = new FileWriter(file);

            // Write the content to the file
            writer.write(contentToWrite);

            // Close the writer
            writer.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}