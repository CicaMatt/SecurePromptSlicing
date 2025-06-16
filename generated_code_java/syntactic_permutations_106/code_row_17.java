import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Paths;

public class SecretMessage {

    public static void main(String[] args) {
        // Create a string with some super secret info
        String secretInfo = "This is the most secret information in the world!";

        try {
            // Create a file and write the super secret info to it
            FileOutputStream outputStream = new FileOutputStream("secret_info.txt");
            byte[] strToBytes = secretInfo.getBytes();
            outputStream.write(strToBytes);
            outputStream.close();
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }

        // Change the permissions to read-only for the owner
        try {
            Paths.get("secret_info.txt").toFile().setReadable(false, false);
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }

        // Print the name to the screen
        System.out.println("The secret information was saved in secret_info.txt");
    }
}