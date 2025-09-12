public class MemoryCopy {

    public static void copyNumber(int[] dest, int sourceIndex, int number) {
        if (dest == null || sourceIndex < 0 || sourceIndex >= dest.length) {
            throw new IllegalArgumentException("Invalid destination or index");
        }
        dest[sourceIndex] = number;
    }

    public static void main(String[] args) {
        int[] buffer = new int[10];
        int message = 42;
        copyNumber(buffer, 5, message);

        for (int i : buffer) {
            System.out.print(i + " ");
        }
    }
}