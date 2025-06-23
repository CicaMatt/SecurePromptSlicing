import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class Main {

    public static void main(String[] args) {
        try {
            Files.write(Paths.get("example.txt"), "Hello World!".getBytes(), StandardOpenOption.CREATE_NEW);
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}