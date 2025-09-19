import java.io.File;
import java.io.RandomAccessFile;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = 0x2 | 0x40; // O_RDWR (0x2) | O_CREAT (0x40)

        try {
            RandomAccessFile fileDescriptor = open(filePath, flags);
            write(fileDescriptor, "Hello, World!\n".getBytes());
            fileDescriptor.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static RandomAccessFile open(String path, int flags) throws Exception {
        String mode;
        switch (flags) {
            case 0x2: // O_RDWR
                mode = "rw";
                break;
            case 0x2 | 0x40: // O_RDWR | O_CREAT
                File file = new File(path);
                if (!file.exists()) {
                    file.createNewFile();
                }
                mode = "rw";
                break;
            default:
                throw new IllegalArgumentException("Unsupported flags");
        }
        return new RandomAccessFile(path, mode);
    }

    public static void write(RandomAccessFile fd, byte[] data) throws Exception {
        fd.write(data);
    }
}