import java.io.File;
import java.io.IOException;

public class CreateConfigFile {
    public static void main(String[] args) {
        File file = new File("important_config");
        try {
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
            } else {
                System.out.println("File already exists.");
            }
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}