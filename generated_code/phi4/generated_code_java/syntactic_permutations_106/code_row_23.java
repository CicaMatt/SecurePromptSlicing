import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecureFile {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("superSecret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (!file.setReadOnly()) {
            System.err.println("Failed to set the file as read-only.");
        }

        System.out.println("The file name is: " + file.getName());
    }
}