import java.io.*;

public class SecretInfo {
    public static void main(String[] args) throws IOException {
        String secretInfo = "My secret info!";
        File secretFile = new File("secret.txt");
        FileOutputStream fos = new FileOutputStream(secretFile);
        fos.write(secretInfo.getBytes());
        if (secretFile.setReadable(true, true)) {
            System.out.println("File created and made read-only for owner.");
        }
    }
}