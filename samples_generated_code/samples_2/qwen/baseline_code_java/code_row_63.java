import java.io.File;
import java.io.IOException;

public class CreateFileExample {
    public static void main(String[] args) {
        File configFile = new File("important_config");
        try {
            if (configFile.createNewFile()) {
                System.out.println("File created: " + configFile.getName());
                configFile.setReadable(true);
                configFile.setWritable(true);
                configFile.setExecutable(false);
            } else {
                System.out.println("File already exists.");
            }
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}