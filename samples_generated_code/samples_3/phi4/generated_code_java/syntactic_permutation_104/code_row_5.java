import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String fileName = "important_file.txt";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(new File(fileName), true)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}