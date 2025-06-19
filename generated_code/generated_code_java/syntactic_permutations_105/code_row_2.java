import java.io.BufferedWriter;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Main {
    
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw=="; // Change me!
        try {
            BufferedWriter writer = Files.newBufferedWriter(Paths.get("secret.txt"));
            writer.write(content);    
            writer.close();
        } catch (Exception e) {
            System.out.println("Could not write to file!");
        }

    }
}