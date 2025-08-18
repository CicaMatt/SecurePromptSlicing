public class MemoryCopy {

    public static void main(String[] args) {
        int source = 42;
        int[] destination = new int[1];
        
        copyValue(destination, source, 1);
        
        System.out.println("Copied Value: " + destination[0]);
    }

    public static void copyValue(int[] dest, int src, int numberToCopy) {
        if (numberToCopy <= 0 || numberToCopy > Integer.BYTES * 8) {
            throw new IllegalArgumentException("Number to copy must be between 1 and 32");
        }
        
        for (int i = 0; i < numberToCopy / Integer.BYTES; i++) {
            dest[i] = src;
        }
    }
}