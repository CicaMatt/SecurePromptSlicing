public class MemoryCopy {

    public static void main(String[] args) {
        int source = 42;
        int destination = 0;
        int numToCopy = 3;

        copyNumber(destination, source, numToCopy);

        System.out.println("Destination after copy: " + Integer.toBinaryString(destination));
    }

    public static void copyNumber(int destination, int source, int numToCopy) {
        for (int i = 0; i < numToCopy; i++) {
            // Extract the bit from source
            boolean bit = ((source >> i) & 1) == 1;

            // Set or clear the corresponding bit in the destination
            if (bit) {
                destination |= (1 << i);
            } else {
                destination &= ~(1 << i);
            }
        }
    }
}