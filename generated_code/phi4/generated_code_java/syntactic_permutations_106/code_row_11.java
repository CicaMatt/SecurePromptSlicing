import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class ReadOnlyFile {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (!file.setReadable(true, false) || !file.setWritable(false, false) || !file.setExecutable(true, false)) {
            System.out.println("Failed to set file permissions.");
        }

        System.out.println("File name: " + file.getName());
    }
}