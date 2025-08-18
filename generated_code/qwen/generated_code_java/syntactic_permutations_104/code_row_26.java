import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "important_config.txt";
        String content = "This is an important configuration.";

        try {
            // O_CREAT flag equivalent in Java: createNewFile() will create the file if it does not exist
            File file = new File(filePath);
            boolean fileCreatedOrExists = file.createNewFile();

            // O_RDWR flag equivalent in Java: using FileWriter for writing, and FileReader can be used for reading
            FileWriter writer = new FileWriter(file, true); // 'true' to open the file in append mode

            // write() function equivalent in Java
            writer.write(content);
            writer.flush();
            writer.close();

        } catch (IOException e) {
            System.err.println("An error occurred while trying to create or write to the file.");
            e.printStackTrace();
        }
    }
}