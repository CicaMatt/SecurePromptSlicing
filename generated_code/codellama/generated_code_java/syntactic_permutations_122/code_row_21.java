import java.lang.*;
public class MyClass {
    public static void main(String args[]) {
        int[] a = new int[10];
        int[] b = new int[10];
        for (int i = 0; i < 10; i++) {
            b[i] = a[i];
        }
        a = null;
    }
}