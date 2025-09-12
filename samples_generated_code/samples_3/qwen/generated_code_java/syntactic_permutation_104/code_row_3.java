import java.io.File;
import java.io.RandomAccessFile;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        String contentToWrite = ".";
        
        try {
            int flags = O_RDWR | O_CREAT;
            RandomAccessFile fileDescriptor = open(filePath, flags);
            
            if (fileDescriptor != null) {
                write(fileDescriptor, contentToWrite);
                fileDescriptor.close();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static final int O_RDWR = 0x2;
    public static final int O_CREAT = 0x40;

    public static RandomAccessFile open(String path, int flags) throws Exception {
        String mode = "";
        
        if ((flags & O_RDWR) != 0) {
            mode += "rw";
        }

        File file = new File(path);
        if (!file.exists() && (flags & O_CREAT) != 0) {
            file.createNewFile();
        }
        
        return new RandomAccessFile(file, mode);
    }

    public static void write(RandomAccessFile fd, String content) throws Exception {
        fd.write(content.getBytes());
    }
}