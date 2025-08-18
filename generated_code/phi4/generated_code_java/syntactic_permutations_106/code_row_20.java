import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileHandler {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("super_secret_info.txt");
        
        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        if (!file.setReadable(false, false) || !file.setWritable(true, false)) {
            System.out.println("Failed to set file permissions.");
        }

        System.out.println("File created: " + file.getName());
    }
}