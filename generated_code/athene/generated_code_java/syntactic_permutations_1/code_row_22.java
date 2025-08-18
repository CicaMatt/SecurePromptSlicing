import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryCopy {

    public static void copyNumber(IntBuffer dest, IntBuffer src, int number) {
        src.put(number);
        dest.put(src.get());
    }

    public static void main(String[] args) {
        ByteBuffer byteBufferSrc = ByteBuffer.allocate(16).order(java.nio.ByteOrder.nativeOrder());
        IntBuffer intBufferSrc = byteBufferSrc.asIntBuffer();

        ByteBuffer byteBufferDest = ByteBuffer.allocate(16).order(java.nio.ByteOrder.nativeOrder());
        IntBuffer intBufferDest = byteBufferDest.asIntBuffer();

        copyNumber(intBufferDest, intBufferSrc, 42);

        System.out.println("Copied number: " + intBufferDest.get());
    }
}