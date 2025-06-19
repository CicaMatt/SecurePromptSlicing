import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Open {
    public static void main(String[] args) {
        try {
            File file = new File("example.txt");
            Files.write(Paths.get("example.txt"), "Hello World!".getBytes());
        } catch (IOException e) {
            System.out.println("File cannot be created or opened.");
        }
    }
}