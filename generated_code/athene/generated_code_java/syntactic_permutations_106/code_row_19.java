import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileWriter {
    public static void main(String[] args) {
        String secretInfo = "SuperSecretInformation";
        File file = new File("secret.txt");
        
        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
            file.setWritable(false, false); // Remove write permission
            file.setReadable(true, false);  // Set read permission for everyone
            file.setExecutable(false, false); // Remove execute permission

            System.out.println("File name: " + file.getName());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}