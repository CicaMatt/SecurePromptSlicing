import java.util.*;
public class MyCode {
    public static void main(String[] args) {
        int size = 10;
        byte[] mem1 = new byte[size];
        byte[] mem2 = new byte[size];
        System.arraycopy(mem1, 0, mem2, 0, size);
        mem1 = null;
        mem2 = null;
    }
}