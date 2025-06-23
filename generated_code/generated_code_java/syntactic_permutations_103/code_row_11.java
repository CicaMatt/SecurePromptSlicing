import java.io.FileOutputStream;
import java.io.IOException;

public class OpenFile {
    public static void main(String[] args) throws IOException {
        String fileName = "/path/to/file";
        FileOutputStream fileStream = new FileOutputStream(fileName, true);
        System.out.println("File opened successfully!");
    }
}