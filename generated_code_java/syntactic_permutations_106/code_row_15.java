import java.io.FileWriter; // Import the FileWriter class
import java.io.IOException;

public class SuperSecret {
    public static void main(String[] args) {
        try {
            String superSecretInfo = "This is top secret.";
            FileWriter myWriter = new FileWriter("secretFile.txt");
            myWriter.write(superSecretInfo);
            myWriter.close();

            // Change to read-only for the owner
            Process process = Runtime.getRuntime().exec("attrib +r secretFile.txt");

            System.out.println("secretFile.txt");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}