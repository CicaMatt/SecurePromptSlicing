import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) throws IOException {
        try (FileOutputStream out = new FileOutputStream("myfile1.txt", true)) {
            out.write("Hello World!".getBytes());
        }
    }
}