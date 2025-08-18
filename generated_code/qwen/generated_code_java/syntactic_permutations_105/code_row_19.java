import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        File file = new File("secret.txt");
        try (FileWriter writer = new FileWriter(file)) {
            writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        boolean isReadOnlySet = file.setReadOnly();
        if (!isReadOnlySet) {
            System.err.println("Failed to set read-only permission.");
        }
    }
}