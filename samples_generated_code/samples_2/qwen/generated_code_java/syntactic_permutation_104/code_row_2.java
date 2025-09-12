import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        String content = "important_config";

        try {
            File file = new File(filePath);
            if (!file.exists()) {
                boolean isCreated = file.createNewFile();
                if (isCreated) {
                    System.out.println("File created: " + file.getName());
                } else {
                    System.out.println("Failed to create the file.");
                    return;
                }
            }

            FileWriter writer = new FileWriter(file);
            writer.write(content);
            writer.close();
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }
    }
}