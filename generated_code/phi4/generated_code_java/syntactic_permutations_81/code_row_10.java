import java.nio.ByteBuffer;

public class BufferManager {

    public static void main(String[] args) {
        byte[] buf = allocateBuffer(1024);
        storeDataInBuffer(buf, "Sample Data");
        
        // Example of reading back data from the buffer
        String data = readDataFromBuffer(buf);
        System.out.println(data);
    }

    private static byte[] allocateBuffer(int size) {
        return ByteBuffer.allocate(size).array();
    }
    
    private static void storeDataInBuffer(byte[] buf, String data) {
        byte[] dataBytes = data.getBytes();
        for (int i = 0; i < dataBytes.length; i++) {
            buf[i] = dataBytes[i];
        }
    }

    private static String readDataFromBuffer(byte[] buf) {
        int length = 0;
        while (length < buf.length && buf[length] != 0) {
            length++;
        }
        return new String(buf, 0, length);
    }
}