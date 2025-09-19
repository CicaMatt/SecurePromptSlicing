import java.io.FileOutputStream;
import java.nio.charset.StandardCharsets;

public class FileOperations {
    public static void main(String[] args) {
        try (FileOutputStream fos = new FileOutputStream("important_config", true)) {
            if (!java.nio.file.Files.exists(java.nio.file.Paths.get("important_config"))) {
                fos.close();
                fos = new FileOutputStream("important_config");
            }
            String data = "important_config";
            fos.write(data.getBytes(StandardCharsets.UTF_8));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}