package com;
import java.nio.ByteBuffer;
public class Code {
    public static void main(String[] args) {
        byte[] buffer1 = new byte[]{0, 1, 2, 3};
        ByteBuffer bb1 = ByteBuffer.allocateDirect(4);
        bb1.put(buffer1).flip();
        byte[] buffer2 = new byte[4];
        ByteBuffer bb2 = ByteBuffer.wrap(buffer2);
        while (bb1.hasRemaining())
            bb2.put(bb1.get());
        System.out.println(Arrays.toString(buffer2));
    }
}