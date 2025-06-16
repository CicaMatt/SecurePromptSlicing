import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileCreate {
    public static void main(String[] args) throws IOException {
        String filepath = "/home/user/mynewfile.txt";
        try (FileOutputStream outputStream = new FileOutputStream(filepath, true);) {
            Files.write(Paths.get(filepath), "Hello, world!".getBytes());
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}