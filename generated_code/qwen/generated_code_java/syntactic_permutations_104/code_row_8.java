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
                boolean isCreated = file.createNewFile();
                if (isCreated) {
                    System.out.println("File created: " + file.getName());
                }
            }

            FileWriter writer = new FileWriter(file, true);
            writer.write(dataToWrite);
            writer.close();

            System.out.println("Data written to the file.");

        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}