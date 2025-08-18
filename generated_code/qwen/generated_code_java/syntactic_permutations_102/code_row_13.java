import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "important_config";
        String contentToWrite = "important_config";

        File file = new File(filePath);

        try (FileOutputStream fos = new FileOutputStream(file, true)) {
            if (!file.exists()) {
                boolean isCreated = file.createNewFile();
                if (!isCreated) {
                    throw new IOException("Failed to create the file.");
                }
            }

            fos.write(contentToWrite.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}