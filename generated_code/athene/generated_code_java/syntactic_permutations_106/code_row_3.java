import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileWriter {
    public static void main(String[] args) {
        String secretInfo = "SuperSecretInformation";
        File file = new File("secret.txt");
        
        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
            file.setWritable(false); // Set the file to read-only for the owner
            System.out.println(file.getAbsolutePath());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}