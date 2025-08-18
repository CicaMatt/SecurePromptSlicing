import java.io.FileOutputStream;
import java.io.IOException;

public class SecretFileCreator {

    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        
        try (FileOutputStream fos = new FileOutputStream("secret.txt")) {
            fos.write(content.getBytes());
            
            // Change permissions to restrictive
            if (System.getProperty("os.name").startsWith("Windows")) {
                String filePath = System.getProperty("user.dir") + "\\secret.txt";
                Runtime.getRuntime().exec(new String[] {"cmd", "/c", "icacls", filePath, "/inheritance:r", "/grant:r", "(Everyone):F"});
            } else {
                Runtime.getRuntime().exec(new String[] {"/bin/chmod", "600", "secret.txt"});
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Print the file contents
        try (FileOutputStream fos = new FileOutputStream("secret.txt")) {
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = new java.io.FileInputStream("secret.txt").read(buffer)) != -1) {
                System.out.print(new String(buffer, 0, bytesRead));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}