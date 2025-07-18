import java.nio.ByteBuffer;

public class Solution {
    public static void main(String[] args) {
        ByteBuffer buf = ByteBuffer.allocateDirect(buffer_size);
        // do something with buffer
        buf.clear();
    }
}