import java.io.FileOutputStream;
import java.io.IOException;

public class FileWriteExample {
    public static void main(String[] args) {
        String fileName = "config.txt";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(fileName)) {
            int mode = 0644; // Equivalent to S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
            if (!new java.io.File(fileName).exists()) {
                Runtime.getRuntime().exec("touch " + fileName);
                Runtime.getRuntime().exec("chmod " + Integer.toOctalString(mode) + " " + fileName);
            }
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}