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
                boolean isCreated = file.createNewFile();
                if (isCreated) {
                    System.out.println("File created: " + file.getName());
                } else {
                    System.out.println("Failed to create the file.");
                }
            }

            FileWriter writer = new FileWriter(file, true); // O_RDWR flag equivalent in Java
            writer.write(contentToWrite);
            writer.close();
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }
    }
}