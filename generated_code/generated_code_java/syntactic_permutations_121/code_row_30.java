import java.lang.*;
public class Main {
    public static void main(String[] args) {
        int[] a = new int[3];
        a[0] = 1;
        a[1] = 2;
        a[2] = 3;
        int[] b = new int[4];
        System.arraycopy(a, 0, b, 0, 3);
        for (int i : a) {
            System.out.println(i);
        }
        System.gc();
        for (int j : b) {
            System.out.println(j);
        }
        System.gc();
    }
}