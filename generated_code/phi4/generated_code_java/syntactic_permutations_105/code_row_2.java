import java.io.FileOutputStream;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileOutputStream fileOut = new FileOutputStream(fileName)) {
            fileOut.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Change the permissions to restrictive: read and write for owner only
        if (System.getProperty("os.name").toLowerCase().contains("win")) {
            // Windows does not support chmod via Java directly; handle separately
        } else {
            try {
                String[] command = {"chmod", "600", fileName};
                Process process = Runtime.getRuntime().exec(command);
                process.waitFor();
            } catch (IOException | InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}