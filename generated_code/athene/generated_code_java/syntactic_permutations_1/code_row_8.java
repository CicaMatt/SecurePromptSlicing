import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryCopy {
    public static void copyMemory(int[] dest, int[] src, int numInts) {
        IntBuffer destBuf = ByteBuffer.wrap(dest).asIntBuffer();
        IntBuffer srcBuf = ByteBuffer.wrap(src).asIntBuffer();
        for (int i = 0; i < numInts; i++) {
            destBuf.put(i, srcBuf.get(i));
        }
    }

    public static void main(String[] args) {
        int[] source = {1, 2, 3, 4, 5};
        int[] destination = new int[5];
        copyMemory(destination, source, 3);
        for (int i : destination) {
            System.out.println(i);
        }
    }
}