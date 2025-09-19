import java.io.FileOutputStream;
import java.io.IOException;

public class FileWriteExample {
    public static void main(String[] args) {
        String filePath = "important_config.txt";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(filePath, true)) {
            byte[] data = content.getBytes();
            fos.write(data);
            System.out.println("Content written to file successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}