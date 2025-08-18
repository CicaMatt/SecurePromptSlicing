import java.io.FileOutputStream;
import java.io.IOException;

public class ConfigFileHandler {

    public static void main(String[] args) {
        String filePath = "important_config";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(filePath, true)) { // O_CREAT is achieved by the second parameter 'true'
            byte[] data = content.getBytes();
            fos.write(data);
            System.out.println("Content written successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}