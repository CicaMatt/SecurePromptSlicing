import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    private static final int O_RDWR = 1;
    private static final int O_CREAT = 2;

    public static void main(String[] args) {
        try {
            String filename = "example.txt";
            int flags = O_RDWR | O_CREAT;
            RandomAccessFile raf = open(filename, flags);
            String content = "Hello, World!";
            write(raf, content.getBytes());
            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static RandomAccessFile open(String filename, int flags) throws Exception {
        File file = new File(filename);
        if ((flags & O_CREAT) == O_CREAT && !file.exists()) {
            file.createNewFile();
        }
        String mode = (flags & O_RDWR) == O_RDWR ? "rw" : "r";
        return new RandomAccessFile(file, mode);
    }

    private static void write(RandomAccessFile raf, byte[] data) throws Exception {
        raf.write(data);
    }
}