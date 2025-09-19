import java.io.File;
import java.io.RandomAccessFile;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = 0x2 | 0x40; // O_RDWR (2) | O_CREAT (64)

        try {
            RandomAccessFile fileDescriptor = open(filePath, flags);
            if (fileDescriptor != null) {
                String dataToWrite = "Hello, World!";
                write(fileDescriptor, dataToWrite.getBytes());
                fileDescriptor.close();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static RandomAccessFile open(String path, int flags) throws Exception {
        String mode;
        if ((flags & 0x2) != 0 && (flags & 0x40) != 0) { // O_RDWR | O_CREAT
            mode = "rw";
        } else {
            throw new IllegalArgumentException("Unsupported flags");
        }
        return new RandomAccessFile(new File(path), mode);
    }

    public static void write(RandomAccessFile fileDescriptor, byte[] data) throws Exception {
        fileDescriptor.write(data);
    }
}