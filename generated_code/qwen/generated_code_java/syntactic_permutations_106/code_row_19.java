import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileWriter {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info that should not be shared.";
        File file = new File("secret_info.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
            System.out.println("Secret info written to: " + file.getName());

            if (!file.setExecutable(false) || !file.setReadable(false, true) || !file.setWritable(true, false)) {
                System.err.println("Failed to set file permissions.");
            } else {
                System.out.println("File permissions changed successfully.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}