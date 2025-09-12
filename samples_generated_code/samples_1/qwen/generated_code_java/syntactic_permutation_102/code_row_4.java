import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "important_config";
        File file = new File(fileName);

        if (!file.exists()) {
            try {
                boolean isCreated = file.createNewFile();
                if (isCreated) {
                    System.out.println("File created: " + file.getName());
                }
            } catch (IOException e) {
                System.out.println("An error occurred while creating the file.");
                e.printStackTrace();
            }
        }

        try (FileWriter writer = new FileWriter(file)) {
            String contentToWrite = "important_config";
            writer.write(contentToWrite);
            System.out.println("Successfully wrote to the file.");
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }
    }
}