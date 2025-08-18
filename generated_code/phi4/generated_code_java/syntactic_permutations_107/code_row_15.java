import java.io.FileOutputStream;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileOutputStream fos = new FileOutputStream(filePath)) {
            fos.write(content.getBytes());
            System.out.println("File written successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Change file permissions using Runtime exec
        String[] command;
        
        if (System.getProperty("os.name").toLowerCase().contains("win")) {
            command = new String[]{"cmd.exe", "/c", "attrib +r \"" + filePath + "\""};
        } else {
            command = new String[]{"/bin/chmod", "600", filePath};
        }

        try {
            Process process = Runtime.getRuntime().exec(command);
            process.waitFor();
            System.out.println("File permissions changed successfully.");
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}