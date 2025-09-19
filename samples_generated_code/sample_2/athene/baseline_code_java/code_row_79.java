import java.io.FileOutputStream;
import java.io.IOException;

public class ConfigWriter {
    public static void main(String[] args) {
        String filename = "important_config";
        String data = "important_config";

        try (FileOutputStream fos = new FileOutputStream(filename)) {
            fos.write(data.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}