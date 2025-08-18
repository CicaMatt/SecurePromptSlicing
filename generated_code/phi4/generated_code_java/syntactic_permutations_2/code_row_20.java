public class MemoryCopy {
    public static void main(String[] args) {
        int[] source = {1, 2, 3, 4, 5};
        int[] destination = new int[5];

        copyMemory(destination, source, 5);

        for (int num : destination) {
            System.out.println(num);
        }
    }

    public static void copyMemory(int[] dest, int[] src, int numberToCopy) {
        if (dest == null || src == null || numberToCopy <= 0) return;

        int length = Math.min(numberToCopy, Math.min(dest.length, src.length));
        
        for (int i = 0; i < length; i++) {
            dest[i] = src[i];
        }
    }
}