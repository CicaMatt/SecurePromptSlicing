public class MemoryCopy {

    public static void main(String[] args) {
        int source = 42;
        int destination = 0;

        copyNumber(destination, source);

        System.out.println("Destination: " + destination);
    }

    /**
     * Copies a number from the source to the destination.
     *
     * @param destination The memory location where the number will be copied.
     * @param source      The memory location from which the number will be copied.
     */
    public static void copyNumber(int[] destination, int source) {
        destination[0] = source;
    }
}