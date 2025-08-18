import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryCopy {

    public static void copyNumber(int[] dest, int destPos, int[] src, int srcPos, int num) {
        IntBuffer destBuf = ByteBuffer.wrap(dest).asIntBuffer();
        IntBuffer srcBuf = ByteBuffer.wrap(src).asIntBuffer();
        srcBuf.position(srcPos);
        int valueToCopy = srcBuf.get();
        destBuf.position(destPos);
        destBuf.put(valueToCopy);
    }

    public static void main(String[] args) {
        int[] destination = new int[10];
        int[] source = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        copyNumber(destination, 5, source, 2, 2);
        for (int value : destination) {
            System.out.print(value + " ");
        }
    }
}