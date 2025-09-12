import java.io.FileOutputStream;
import java.io.IOException;

public class ConfigFileHandler {
    public static void main(String[] args) {
        String filePath = "important_config";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(filePath, true)) {
            fos.write((content + "\n").getBytes());
            System.out.println("Content written to file successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}