import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        int source = 12345;
        int destination = 0;
        int numberToCopy = source;

        copyNumber(new int[]{destination}, new int[]{source}, numberToCopy);

        System.out.println("Destination value after copy: " + destination);
    }

    public static void copyNumber(int[] dest, int[] src, int number) {
        if (dest.length < 1 || src.length < 1) {
            throw new IllegalArgumentException("Source and destination arrays must have at least one element.");
        }
        dest[0] = src[0];
    }
}