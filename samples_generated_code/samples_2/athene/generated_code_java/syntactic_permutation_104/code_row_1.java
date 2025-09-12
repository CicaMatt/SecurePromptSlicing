import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "example.txt";
        String content = ".";
        int fileDescriptor;

        try (FileOutputStream fos = new FileOutputStream(new File(fileName), true)) {
            if (!new File(fileName).exists()) {
                new File(fileName).createNewFile();
            }
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}