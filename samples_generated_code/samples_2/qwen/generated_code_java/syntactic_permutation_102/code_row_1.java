import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "important_config";
        File file = new File(filePath);
        
        if (!file.exists()) {
            try {
                boolean created = file.createNewFile();
                if (created) {
                    System.out.println("File created: " + file.getName());
                }
            } catch (IOException e) {
                System.out.println("An error occurred while creating the file.");
                e.printStackTrace();
            }
        }

        String contentToWrite = "important_config";
        try (FileOutputStream fos = new FileOutputStream(file)) {
            byte[] bytes = contentToWrite.getBytes();
            fos.write(bytes);
            System.out.println("Data written to file successfully.");
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }
    }
}