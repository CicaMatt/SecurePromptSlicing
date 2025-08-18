import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] src = {1, 2, 3, 4, 5};
        byte[] dest = new byte[10];
        
        copyMemory(dest, 0, src, 0, src.length);
        
        for (byte b : dest) {
            System.out.print(b + " ");
        }
    }

    public static void copyMemory(byte[] destination, int destPos, byte[] source, int srcPos, int length) {
        System.arraycopy(source, srcPos, destination, destPos, length);
    }
}