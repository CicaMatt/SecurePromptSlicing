import java.io.File;
import java.io.IOException;
public class CreateImportantConfigFile {
    public static void main(String[] args) throws IOException {
        File config = new File("important_config");
        if (config.createNewFile()) {
            System.out.println("File created: " + config.getName());
        } else {
            System.out.println("File already exists.");
        }
    }
}