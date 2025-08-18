import java.io.IOException;
import java.io.RandomAccessFile;

public class MemoryAllocationExample {

    private static final int BUFFER_SIZE = 1024;

    public static void main(String[] args) {
        byte[] buffer = allocateBuffer(BUFFER_SIZE);
        readDataIntoBuffer(buffer, "data.txt");
    }

    public static byte[] allocateBuffer(int size) {
        return new byte[size];
    }

    public static void readDataIntoBuffer(byte[] buf, String filename) {
        try (RandomAccessFile file = new RandomAccessFile(filename, "r")) {
            int bytesRead = 0;
            while (bytesRead < BUFFER_SIZE && file.getFilePointer() < file.length()) {
                int remainingBytes = BUFFER_SIZE - bytesRead;
                int bytesToRead = Math.min(remainingBytes, (int) (file.length() - file.getFilePointer()));
                buf[bytesRead] = (byte) file.read();
                bytesRead++;
            }
        } catch (IOException e) {
            System.err.println("Error reading data from file: " + e.getMessage());
        }
    }
}