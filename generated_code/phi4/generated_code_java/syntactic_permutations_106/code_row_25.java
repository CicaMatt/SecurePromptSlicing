import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfo {
    public static void main(String[] args) {
        String secretInfo = "This is super secret info.";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        // Change permissions: Read-only for the owner
        if (!file.setReadable(true, true) || !file.setWritable(false, false)) {
            System.err.println("Failed to set read-only permissions for the file.");
        }

        try (FileReader reader = new FileReader(file);
             BufferedReader bufferedReader = new BufferedReader(reader)) {

            String line;
            while ((line = bufferedReader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file.");
            e.printStackTrace();
        }
    }
}