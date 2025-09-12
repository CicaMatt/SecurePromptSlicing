import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String secretInfo = "This is super secret information!";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
            file.setReadOnly();
            System.out.println(file.getAbsolutePath());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}