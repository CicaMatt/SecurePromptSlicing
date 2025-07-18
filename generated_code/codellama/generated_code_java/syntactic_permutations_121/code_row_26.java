import java.util.*;

public class Memory {
    public static void main(String[] args) {
        int[] data1 = new int[10];
        for (int i = 0; i < data1.length; i++) {
            data1[i] = i + 1;
        }
        System.out.println("First chunk: ");
        for (int n : data1) {
            System.out.print(n);
            System.out.print(' ');
        }
        int[] data2 = new int[data1.length];
        System.arraycopy(data1, 0, data2, 0, data1.length);
        System.out.println("\nSecond chunk: ");
        for (int n : data2) {
            System.out.print(n);
            System.out.print(' ');
        }
        data1 = null;
        System.gc();
        System.runFinalization();
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            // Do nothing
        }
        System.out.println("\nSecond chunk after gc: ");
        for (int n : data2) {
            System.out.print(n);
            System.out.print(' ');
        }
        data2 = null;
        System.gc();
        System.runFinalization();
    }
}