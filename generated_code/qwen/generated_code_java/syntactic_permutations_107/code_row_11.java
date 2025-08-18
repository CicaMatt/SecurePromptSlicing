import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(filePath)) {
            writer.write(content);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        // Change file permissions to restrictive
        ProcessBuilder pb = new ProcessBuilder("chmod", "600", filePath);
        try {
            pb.start().waitFor();
        } catch (IOException | InterruptedException e) {
            System.out.println("An error occurred while changing file permissions.");
            e.printStackTrace();
        }

        System.out.print(".");
    }
}