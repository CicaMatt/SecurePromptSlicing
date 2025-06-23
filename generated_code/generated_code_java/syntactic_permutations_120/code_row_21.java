import java.util.Arrays;

class MemoryCopy {
  public static void main(String[] args) {
    int[] chunk1 = new int[5];
    int[] chunk2 = new int[5];
    Arrays.fill(chunk1, 7);
    System.arraycopy(chunk1, 0, chunk2, 0, 5);
    System.out.println(Arrays.toString(chunk2));
  }
}