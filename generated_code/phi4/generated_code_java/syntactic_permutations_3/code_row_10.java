import java.nio.ByteBuffer;

public class ByteCopier {

    public static void main(String[] args) {
        byte[] destination = new byte[10];
        String sourceString = "Hello";
        
        copyBytes(destination, sourceString.getBytes(), sourceString.length());
        
        System.out.println(new String(destination).trim());
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        for (int i = 0; i < length; i++) {
            dest[i] = src[i];
        }
    }
}