import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {
    public static void main(String[] args) {
        String filename = "important_config";
        int flags = 0x242; // O_CREAT | O_RDWR in octal (0600 | 0664)
        try {
            File file = new File(filename);
            if (!file.exists()) {
                boolean created = file.createNewFile();
                if (created) {
                    file.setReadable(true, false); // readable by all
                    file.setWritable(true, true);  // writable by owner only
                }
            }

            FileOutputStream fos = new FileOutputStream(file, true);
            String content = "Config data";
            fos.write(content.getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}