import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {
    public static void main(String[] args) {
        String filePath = "important_config";
        File file = new File(filePath);
        
        try (FileOutputStream fos = new FileOutputStream(file, true)) {
            if (!file.exists()) {
                file.createNewFile();
            }
            String data = "important_config";
            fos.write(data.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}