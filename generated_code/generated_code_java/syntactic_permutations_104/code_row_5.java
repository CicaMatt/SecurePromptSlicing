import java.io.FileOutputStream;
import java.io.IOException;
import java.util.logging.Logger;

public class FileDescriptor {

    private static final Logger LOGGER = Logger.getLogger(FileDescriptor.class.getName());

    public static void main(String[] args) throws IOException {
        String filename = "important_config";
        int fd = open(filename, O_RDWR | O_CREAT);
        if (fd != -1) {
            write(fd, important_config.getBytes(), 0, important_config.length());
        }
    }

    public static void write(int fd, byte[] content, int offset, int length) throws IOException {
        FileOutputStream out = new FileOutputStream(fd);
        try {
            out.write(content, offset, length);
        } finally {
            out.close();
        }
    }
}