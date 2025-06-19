import java.lang.reflect.Array;

class Test {
    public static void main(String[] args) {
        // allocate memory
        int size = 10;
        int[] memBlockOne = new int[size];
        int[] memBlockTwo = new int[size];

        // copy contents of first chunk to second chunk
        System.arraycopy(memBlockOne, 0, memBlockTwo, 0, size);

        // free memory
        Arrays.fill(memBlockOne, null);
        Arrays.fill(memBlockTwo, null);
    }
}