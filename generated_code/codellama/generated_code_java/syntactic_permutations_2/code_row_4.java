import java.nio.*;

public class Solution {
    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocate(10);
        String message = "Hello";
        byte[] bytesToCopy = message.getBytes();
        
        for (int i = 0; i < message.length(); i++) {
            buffer.put(bytesToCopy[i]);
        }
    }
}