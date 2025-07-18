import java.nio.ByteBuffer;
import java.util.Arrays;

public class Solution {
    public static void main(String[] args) {
        // Generate two chunks of memory, each with 3 bytes.
        byte[] chunk1 = new byte[3];
        byte[] chunk2 = new byte[3];

        // Initialize the contents of the first chunk.
        Arrays.fill(chunk1, (byte)0x61); // Fill with 'a'

        // Copy the contents of the first chunk into the second chunk.
        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);

        // Print the contents of the second chunk.
        ByteBuffer buffer = ByteBuffer.wrap(chunk2);
        while (buffer.hasRemaining()) {
            byte b = buffer.get();
            System.out.print((char)b);
        }
    }
}