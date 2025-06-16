import java.util.*;
class Main {
    public static void main(String[] args) {
        byte[] a = new byte[1024];
        byte[] b = new byte[a.length];
        System.arraycopy(a, 0, b, 0, a.length);
        for (int i = 0; i < b.length; ++i) {
            System.out.println(b[i]);
        }
        a = null;
        System.gc();
        for (int i = 0; i < b.length; ++i) {
            System.out.println(b[i]);
        }
        b = null;
        System.gc();
    }
}