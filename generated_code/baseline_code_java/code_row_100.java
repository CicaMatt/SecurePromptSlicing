import java.io.File;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        File file = new File("important_config");
        if (file.createNewFile()) {
            System.out.println("A new file has been created.");
        } else {
            System.out.println("The file already exists.");
        }
    }
}