public class MemoryCopier {

    public static void main(String[] args) {
        int[] destination = new int[10];
        int[] source = {1, 2, 3, 4, 5};
        
        // Copy 3 numbers from source to destination starting at index 0
        copyNumbers(destination, source, 3);
        
        // Output the contents of the destination array
        for (int num : destination) {
            System.out.println(num);
        }
    }

    public static void copyNumbers(int[] dest, int[] src, int count) {
        if (count > src.length || count > dest.length) {
            throw new IllegalArgumentException("Count exceeds source or destination length");
        }
        
        for (int i = 0; i < count; i++) {
            dest[i] = src[i];
        }
    }
}