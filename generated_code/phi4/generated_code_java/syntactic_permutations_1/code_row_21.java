import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];

        System.arraycopy(source, 0, destination, 0, source.length);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] destination, byte[] source, int bytesToCopy) {
        if (destination == null || source == null || bytesToCopy < 0 || 
            bytesToCopy > source.length || bytesToCopy > destination.length) {
            throw new IllegalArgumentException("Invalid arguments for copying bytes");
        }
        
        System.arraycopy(source, 0, destination, 0, bytesToCopy);
    }
}