import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] destination = new byte[10];
        String message = "Hello";
        
        copyBytes(destination, message.getBytes(), message.length());
        
        System.out.println(new String(destination).trim()); // Output: Hello
    }
    
    public static void copyBytes(byte[] dest, byte[] src, int num) {
        ByteBuffer destBuffer = ByteBuffer.wrap(dest);
        ByteBuffer srcBuffer = ByteBuffer.wrap(src);
        
        for (int i = 0; i < num; i++) {
            destBuffer.put(i, srcBuffer.get(i));
        }
    }
}