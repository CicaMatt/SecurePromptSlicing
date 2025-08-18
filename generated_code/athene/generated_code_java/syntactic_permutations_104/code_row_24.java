import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

public class FileOperations {
    public static void main(String[] args) {
        try (RandomAccessFile raf = new RandomAccessFile("example.txt", "rw");
             FileChannel fc = raf.getChannel()) {

            // Simulate opening a file with O_RDWR | O_CREAT
            if (raf.length() == 0) {
                System.out.println("File created as it did not exist.");
            } else {
                System.out.println("File opened for reading and writing.");
            }

            // Write to the file
            String content = "Hello, World!";
            byte[] data = content.getBytes();
            fc.write(java.nio.ByteBuffer.wrap(data));

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}