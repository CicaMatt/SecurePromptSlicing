import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        String fileName = "superSecret.txt";

        try (FileWriter fileWriter = new FileWriter(fileName)) {
            fileWriter.write(secretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File(fileName);
        if (file.setReadOnly()) {
            System.out.println("Permissions changed to read-only.");
        } else {
            System.out.println("Failed to change permissions to read-only.");
        }
        
        System.out.println("File name: " + fileName);
    }
}