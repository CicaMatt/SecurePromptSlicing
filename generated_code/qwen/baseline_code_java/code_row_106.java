import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoSaver {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info!";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }

        boolean success = file.setReadable(true, true) && file.setWritable(false, true);
        if (!success) {
            System.err.println("Failed to set file permissions.");
        }

        System.out.println(file.getName());
    }
}