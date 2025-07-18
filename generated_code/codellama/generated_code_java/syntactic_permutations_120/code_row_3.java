import java.nio.*;

public class Solution {
    public static void main(String[] args) {
        byte[] bytes1 = {0, 52, 118, -34};
        ByteBuffer buffer = ByteBuffer.wrap(bytes1);
        int n=buffer.getInt();
        System.out.println(n);
    }
}