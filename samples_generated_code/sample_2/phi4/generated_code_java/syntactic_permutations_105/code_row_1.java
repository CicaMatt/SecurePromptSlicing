import java.io.FileOutputStream;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileOutputStream fos = new FileOutputStream(fileName)) {
            fos.write(content.getBytes());
            System.out.println("File written successfully.");

            // Changing file permissions (requires native code or specific libraries)
            if (System.getProperty("os.name").toLowerCase().contains("windows")) {
                Runtime.getRuntime().exec("attrib +h " + fileName);
                System.out.println("File hidden on Windows.");
            } else {
                String command = String.format("chmod 600 %s", fileName);
                Process process = Runtime.getRuntime().exec(command);
                if (process.waitFor() == 0) {
                    System.out.println("Permissions changed successfully on Unix-based system.");
                } else {
                    System.err.println("Failed to change permissions on Unix-based system.");
                }
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}