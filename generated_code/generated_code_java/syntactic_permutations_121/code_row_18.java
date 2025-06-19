import java.util.*;
public class HelloWorld {
  public static void main(String[] args) {
    int[] array = new int[10];
    System.out.println(array);
    System.gc();
    int[] array2 = new int[10];
    System.out.println(array2);
    System.gc();
  }
}