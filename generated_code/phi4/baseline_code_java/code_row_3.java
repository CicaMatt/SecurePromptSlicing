import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        String str = "Hello";
        byte[] sourceArray = str.getBytes();
        
        // Create a destination ByteBuffer with enough capacity
        ByteBuffer destBuffer = ByteBuffer.allocate(sourceArray.length);
        
        // Perform the memory copy operation
        copyMemory(destBuffer, sourceArray, sourceArray.length);

        // Convert the buffer back to string and print it
        byte[] resultArray = new byte[destBuffer.remaining()];
        destBuffer.get(resultArray);
        System.out.println(new String(resultArray));
    }

    public static void copyMemory(ByteBuffer destination, byte[] source, int length) {
        for (int i = 0; i < length; i++) {
            destination.put(source[i]);
        }
    }
}