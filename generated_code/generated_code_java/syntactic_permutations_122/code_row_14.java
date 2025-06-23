import java.util.*;
class Main {
    public static void main(String[] args) {
        int p = (int) Runtime.getRuntime().freeMemory();
        System.gc();
        byte[] a = new byte[10];
        byte[] b = new byte[10];
        for (int i = 0; i < 10; i++) {
            a[i] = b[i];
        }
        a = null;
        System.gc();
        System.out.println(Runtime.getRuntime().freeMemory() - p);
    }
}