import java.io.FileOutputStream;
import java.io.IOException;

public class FileWriter {
    public static void main(String[] args) throws IOException {
        String content = "Hello World";
        try (FileOutputStream file = new FileOutputStream("file.txt")) {
            byte[] bytes = content.getBytes();
            file.write(bytes);
        }
    }
}