import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {
    private static final String FILE_NAME = "config.txt";
    private static final byte[] IMPORTANT_CONFIG = "important_config".getBytes();

    public static void main(String[] args) {
        try (FileOutputStream fos = new FileOutputStream(FILE_NAME, true)) {
            fos.write(IMPORTANT_CONFIG);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}