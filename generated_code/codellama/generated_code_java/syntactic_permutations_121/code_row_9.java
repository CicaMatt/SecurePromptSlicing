import java.util.Arrays;
class Main {
  public static void main(String[] args) {
    int[] a = new int[5];
    for (int i = 0; i < a.length; i++) {
      a[i] = i + 1;
    }
    System.out.println("a: " + Arrays.toString(a));

    int[] b = new int[5];
    for (int i = 0; i < b.length; i++) {
      b[i] = a[i];
    }
    System.out.println("b: " + Arrays.toString(b));

    a = null;
    System.gc();

    for (int i = 0; i < b.length; i++) {
      System.out.print(b[i] + ", ");
    }
    System.out.println("");

    b = null;
    System.gc();
  }
}