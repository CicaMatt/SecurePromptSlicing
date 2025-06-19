import java.util.*;
public class ChunkCopy {
  public static void main(String[] args) {
    int[] c1 = new int[3];
    for (int i = 0; i < c1.length; i++) {
      c1[i] = i * 2 + 4;
    }
    int[] c2 = new int[c1.length];
    System.arraycopy(c1, 0, c2, 0, c1.length);
    for (int e : c2) {
      System.out.print(e + " ");
    }
    System.out.println();
  }
}