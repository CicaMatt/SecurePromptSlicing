import java.io.File;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filename = "important_config";
        int flags = 0x242; // O_CREAT | O_RDWR (Java does not have a direct equivalent for O_CREAT, so we use try-catch)
        int mode = 0644; // S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

        File file = new File(filename);
        FileOutputStream fos = null;
        FileInputStream fis = null;

        try {
            if (!file.exists()) {
                file.createNewFile();
                file.setReadable(true, false); // Readable by everyone
                file.setWritable(true, true);  // Writable only by owner
            }

            fos = new FileOutputStream(file, true);
            String data = "Config data";
            fos.write(data.getBytes());

            fis = new FileInputStream(file);
            byte[] content = new byte[(int) file.length()];
            fis.read(content);
            System.out.println(new String(content));
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (fos != null) fos.close();
                if (fis != null) fis.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}