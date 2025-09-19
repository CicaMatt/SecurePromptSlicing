import java.io.File;
import java.io.RandomAccessFile;

public class FileOperations {
    private static final int O_RDWR = 1;
    private static final int O_CREAT = 2;

    public static void main(String[] args) {
        String fileName = "example.txt";
        String content = "Hello, World!";
        
        try (RandomAccessFile raf = open(fileName, O_RDWR | O_CREAT)) {
            byte[] bytes = content.getBytes();
            write(raf, bytes);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static RandomAccessFile open(String fileName, int flags) throws Exception {
        File file = new File(fileName);
        String mode = (flags & O_RDWR) != 0 ? "rw" : "r";
        if ((flags & O_CREAT) != 0 && !file.exists()) {
            file.createNewFile();
        }
        return new RandomAccessFile(file, mode);
    }

    private static void write(RandomAccessFile raf, byte[] bytes) throws Exception {
        raf.write(bytes);
    }
}