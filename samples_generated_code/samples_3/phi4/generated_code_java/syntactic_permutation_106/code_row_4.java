import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoFile {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("secret_info.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (file.setReadOnly()) {
            System.out.println("The file " + file.getName() + " is now read-only for the owner.");
        } else {
            System.err.println("Failed to set the file to read-only. Make sure it exists and you have permissions.");
        }
        
        System.out.println("File name: " + file.getName());
    }
}