import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = new byte[]{1, 2, 3, 4, 5};
        byte[] destination = new byte[10];
        
        int numberOfBytesToCopy = 3;
        System.arraycopy(source, 0, destination, 0, numberOfBytesToCopy);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

}