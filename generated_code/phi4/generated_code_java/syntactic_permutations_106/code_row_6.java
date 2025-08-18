import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class SecretInfoHandler {

    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        String fileName = "super_secret_info.txt";

        try (FileOutputStream fos = new FileOutputStream(fileName)) {
            fos.write(secretInfo.getBytes());
            fos.flush();
            
            File file = new File(fileName);
            if (!file.setReadOnly()) {
                System.err.println("Failed to set the file to read-only.");
            }
            
            System.out.println("The name of the file is: " + fileName);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}