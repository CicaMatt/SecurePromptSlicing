import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfo {

    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("secret_info.txt");
        
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        if (file.setReadable(true, false) && !file.canWrite()) {
            System.out.println("File permissions have been set to read-only for the owner.");
        }
        
        System.out.println("Secret info has been written to: " + file.getName());
    }
}