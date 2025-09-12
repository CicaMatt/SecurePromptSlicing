import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocate(1024);
        int sourceIndex = 5;
        int destinationIndex = 10;
        int numberToCopy = 789;

        // Initialize source location with a value
        buffer.putInt(sourceIndex, numberToCopy);

        // Copy the number from source to destination
        copyNumber(buffer, destinationIndex, sourceIndex);

        // Verify the copy
        System.out.println("Original number at source: " + buffer.getInt(sourceIndex));
        System.out.println("Copied number at destination: " + buffer.getInt(destinationIndex));
    }

    public static void copyNumber(ByteBuffer destination, int destIndex, int sourceIndex) {
        int number = destination.getInt(sourceIndex);
        destination.putInt(destIndex, number);
    }
}