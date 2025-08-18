import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(fileName, "rwd");
            File file = raf.getChannel().open();
            
            int flags = 0;
            boolean create = (flags & O_CREAT) != 0;
            boolean truncate = (flags & O_TRUNC) != 0;
            boolean writeOnly = (flags & O_WRONLY) != 0;
            boolean exclusive = (flags & O_EXCL) != 0;

            if (create && !file.exists()) {
                file.createNewFile();
            }
            if (truncate && file.exists()) {
                file.setLength(0);
            }
            if (writeOnly && !raf.getFD().valid()) {
                throw new IllegalArgumentException("File not opened for writing");
            }
            if (exclusive && file.exists()) {
                throw new IllegalArgumentException("File already exists");
            }

            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static final int O_CREAT = 0x01;
    private static final int O_TRUNC = 0x02;
    private static final int O_WRONLY = 0x04;
    private static final int O_EXCL = 0x08;
}