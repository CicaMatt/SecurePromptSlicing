import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_RDWR | O_CREAT;
        try {
            int fileDescriptor = open(filePath, flags);
            String dataToWrite = "Hello, world!";
            write(fileDescriptor, dataToWrite.getBytes());
            System.out.println("Data written to file.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static final int O_RDWR = 0x2;
    public static final int O_CREAT = 0x40;

    public static int open(String path, int flags) throws IOException {
        File file = new File(path);
        if ((flags & O_CREAT) == O_CREAT && !file.exists()) {
            file.createNewFile();
        }
        return 0; // In a real scenario, this would be a valid file descriptor
    }

    public static void write(int fd, byte[] data) throws IOException {
        FileOutputStream fos = new FileOutputStream("example.txt", true);
        fos.write(data);
        fos.close();
    }
}