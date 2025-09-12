import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {

    public static void main(String[] args) {
        String filePath = "important_config.txt";
        String content = "Important configuration data";

        int fd = open(filePath, true);
        if (fd != -1) {
            write(fd, content);
            close(fd);
        }
    }

    private static int open(String filePath, boolean createIfNotExists) {
        FileOutputStream fos = null;
        try {
            int flags = createIfNotExists ? FileOutputStream.APPEND | FileOutputStream.CREATE : FileOutputStream.APPEND;
            fos = new FileOutputStream(filePath, true);
            return 1; // Simulating a file descriptor
        } catch (IOException e) {
            e.printStackTrace();
            return -1;
        }
    }

    private static void write(int fd, String data) {
        if (fd != -1) {
            try (FileOutputStream fos = new FileOutputStream("important_config.txt", true)) {
                fos.write(data.getBytes());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private static void close(int fd) {
        // No-op for this simulation, as resources are managed by try-with-resources
    }
}