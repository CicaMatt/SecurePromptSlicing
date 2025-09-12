import java.io.FileOutputStream;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileOutputStream fos = new FileOutputStream(filePath)) {
            byte[] data = content.getBytes();
            fos.write(data);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}