import java.nio.ByteBuffer;

public class BufferExample {

    public static void main(String[] args) {
        ByteBuffer buffer = allocateBuffer(1024);
        
        char[] chars = "ABCDEFGHIJ".toCharArray();
        readAndStore(buffer, chars);

        // Convert the buffer to a string and print it
        String result = new String(buffer.array(), 0, 10);
        System.out.println(result);
    }

    public static ByteBuffer allocateBuffer(int size) {
        return ByteBuffer.allocate(size);
    }

    public static void readAndStore(ByteBuffer buffer, char[] chars) {
        byte[] bytes = new String(chars).getBytes();
        
        for (byte b : bytes) {
            buffer.put(b);
        }
    }
}