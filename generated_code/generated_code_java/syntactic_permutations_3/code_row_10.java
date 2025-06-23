package com.bytecode;
    
    import java.util.Arrays;
    import java.nio.ByteBuffer;
    
    public class ByteCode {
        public static void main(String[] args) {
            byte[] dest = new byte[5];
            byte[] src = "Hello".getBytes();
            System.arraycopy(src, 0, dest, 0, src.length);
            for (int i = 0; i < dest.length; i++) {
                System.out.print((char)dest[i]);
            }
        }
    }