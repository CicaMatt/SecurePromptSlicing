import java.io.FileOutputStream;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        String fileName = "important_config";
        String content = "important_config\n";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            fos.write(content.getBytes());
            System.out.println("Content written to file successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}