import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filename = "config.txt";
        String content = "important_config";
        try (FileOutputStream fos = new FileOutputStream(new File(filename), true)) {
            if (!new File(filename).exists()) {
                new File(filename).createNewFile();
            }
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}