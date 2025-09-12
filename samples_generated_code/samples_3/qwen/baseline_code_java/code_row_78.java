import java.io.File;
import java.io.IOException;

public class CreateFile {
    public static void main(String[] args) {
        File configFile = new File("important_config");
        try {
            if (configFile.createNewFile()) {
                // Set file permissions to be readable and writable by the owner only
                configFile.setReadable(true, true);
                configFile.setWritable(true, true);
                configFile.setExecutable(false, true);
            }
        } catch (IOException e) {
            System.out.println("An error occurred while creating the file.");
            e.printStackTrace();
        }
    }
}