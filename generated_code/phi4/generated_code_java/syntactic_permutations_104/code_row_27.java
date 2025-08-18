import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";
        String content = ".\n";

        try (FileOutputStream fos = new FileOutputStream(new File(filePath), true)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}