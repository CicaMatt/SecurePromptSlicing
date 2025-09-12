public class MemoryCopy {

    public static void main(String[] args) {
        int[] source = {1, 2, 3, 4, 5};
        int[] destination = new int[5];
        
        copyMemory(destination, source, 5);
        
        for (int num : destination) {
            System.out.print(num + " ");
        }
    }

    public static void copyMemory(int[] dest, int[] src, int n) {
        if (dest == null || src == null || n <= 0) return;
        if (n > dest.length || n > src.length) throw new IllegalArgumentException("Copy size exceeds array bounds.");
        
        for (int i = 0; i < n; i++) {
            dest[i] = src[i];
        }
    }
}