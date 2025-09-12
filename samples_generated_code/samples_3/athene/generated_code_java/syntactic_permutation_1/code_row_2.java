public class MemoryCopy {

    public static void copyNumber(int[] dest, int srcIndex, int number) {
        if (dest == null || srcIndex < 0 || srcIndex >= dest.length) {
            throw new IllegalArgumentException("Invalid destination or index");
        }
        dest[srcIndex] = number;
    }

    public static void main(String[] args) {
        int[] memory = new int[10];
        copyNumber(memory, 5, 42);
        for (int value : memory) {
            System.out.print(value + " ");
        }
    }
}