import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "important_config";
        try (FileOutputStream fos = new FileOutputStream(filePath, true)) {
            // The file is opened for reading and writing.
            // If the file does not exist, it will be created.
            // Java's FileOutputStream does not directly support setting permissions like S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH,
            // so you may need to use a command-line tool or operating system specific API to set these permissions.
            
            String data = "Sample data";
            fos.write(data.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}