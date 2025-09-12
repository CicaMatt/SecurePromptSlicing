import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfo {

    public static void main(String[] args) {
        String superSecretInfo = "This is some super secret info.";
        File file = new File("super_secret_info.txt");

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
            writer.write(superSecretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (file.setReadable(true, false)) { // Set to readable for owner only
            file.setWritable(false, false);   // Remove write permission for everyone
        }

        System.out.println("File written: " + file.getName());
    }
}