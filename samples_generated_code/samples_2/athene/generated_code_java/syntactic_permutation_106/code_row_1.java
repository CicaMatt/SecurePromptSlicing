import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String secretInfo = "SuperSecretInfo123";
        File file = new File("secret.txt");
        
        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
            file.setWritable(false, true); // Set the file to read-only for the owner
            System.out.println(file.getName());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}