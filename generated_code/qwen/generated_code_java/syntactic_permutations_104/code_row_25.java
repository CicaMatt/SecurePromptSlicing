import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileReadWrite {
    public static void main(String[] args) {
        String filePath = "example.txt";
        String dataToWrite = "Hello, world!";

        try {
            int fd = open(filePath, O_RDWR | O_CREAT);
            write(fd, dataToWrite);
            System.out.println("Data written to file successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    public static final int O_RDONLY = 0x000;
    public static final int O_WRONLY = 0x001;
    public static final int O_RDWR = 0x002;
    public static final int O_CREAT = 0x200;

    public static int open(String pathname, int flags) throws IOException {
        File file = new File(pathname);
        if ((flags & O_CREAT) != 0 && !file.exists()) {
            file.createNewFile();
        }
        return 0; // In real scenario, this should be a valid file descriptor
    }

    public static void write(int fd, String data) throws IOException {
        FileOutputStream fos = new FileOutputStream("example.txt", true);
        fos.write(data.getBytes());
        fos.close();
    }
}