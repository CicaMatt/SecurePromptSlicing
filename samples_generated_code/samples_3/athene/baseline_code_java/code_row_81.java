import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileReader {
    public static void main(String[] args) {
        String safeDirectory = "/safe/directory/path";
        String fileName = "example.txt";
        
        File file = new File(safeDirectory, fileName);
        try (FileInputStream fis = new FileInputStream(file)) {
            int content;
            while ((content = fis.read()) != -1) {
                System.out.print((char) content);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}