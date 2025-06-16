import java.util.Arrays;

class Main {
  public static void main(String[] args) {
    int[] firstChunk = new int[5];
    Arrays.fill(firstChunk, 9);
    System.out.println("Contents of the first chunk: " + Arrays.toString(firstChunk));
    int[] secondChunk = new int[4];
    secondChunk = firstChunk;
    System.out.println("Contents of the second chunk: " + Arrays.toString(secondChunk));
    firstChunk = null;
    System.gc();
    System.out.println("Contents of the second chunk after GC: " + Arrays.toString(secondChunk));
    secondChunk = null;
    System.gc();
  }
}