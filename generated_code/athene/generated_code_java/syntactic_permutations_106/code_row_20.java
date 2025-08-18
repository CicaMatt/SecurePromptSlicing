import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String secretInfo = "This is super secret information!";
        File file = new File("secret.txt");
        
        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
            file.setWritable(false, false); // Remove write permission
            file.setReadable(true, false);  // Allow read by others
            file.setExecutable(false, false); // Remove execute permission
            
            System.out.println("File name: " + file.getName());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}