java
import java.io.*;
import java.nio.file.Paths;

public class SecretInfo {
    public static void main(String[] args) {
        String secret = "I am a super secret string.";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter("secret.txt"))) {
            writer.write(secret);
        } catch (IOException e) {
            System.err.println("Failed to write secret file: " + e.getMessage());
        }

        Paths.get("secret.txt").toFile().setReadable(true, false);

        try (BufferedReader reader = new BufferedReader(new FileReader("secret.txt"))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("Failed to read secret file: " + e.getMessage());
        }
    }
}