import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFile {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        
        try (FileWriter writer = new FileWriter("secret.txt")) {
            writer.write(secretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File("secret.txt");

        // Set permissions to read-only for the owner
        if (!file.setReadable(true, false)) {
            System.err.println("Unable to set the file to read only.");
        }
        if (!file.setWritable(false, false)) {
            System.err.println("Unable to remove write permission from the owner.");
        }

        System.out.println(file.getName());
    }
}