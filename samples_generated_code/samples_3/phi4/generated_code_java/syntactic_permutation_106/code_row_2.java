import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String secretInfo = "Super secret info";
        String fileName = "secret.txt";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        File file = new File(fileName);

        if (!file.setReadOnly()) {
            System.out.println("Failed to set the file to read-only.");
        } else {
            System.out.println("The file has been set to read-only.");
        }

        System.out.println("File name: " + fileName);
    }
}