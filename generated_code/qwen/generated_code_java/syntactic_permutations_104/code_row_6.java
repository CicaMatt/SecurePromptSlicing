import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        String dataToWrite = "important_config";

        try {
            // Open the file for reading and writing, create if it doesn't exist
            File file = new File(filePath);
            FileWriter writer = new FileWriter(file);

            // Write the string to the file
            writer.write(dataToWrite);
            writer.close();
        } catch (IOException e) {
            System.out.println("An error occurred while opening or writing to the file.");
            e.printStackTrace();
        }
    }
}