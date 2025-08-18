import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        int source = 42;
        int destination = 0;
        int numberToCopy = source;

        copyNumber(new int[]{destination}, new int[]{source}, numberToCopy);

        System.out.println("Copied Number: " + destination);
    }

    public static void copyNumber(int[] destination, int[] source, int numberToCopy) {
        if (destination.length == 0 || source.length == 0) {
            throw new IllegalArgumentException("Source and Destination arrays must not be empty.");
        }
        destination[0] = source[0];
    }
}