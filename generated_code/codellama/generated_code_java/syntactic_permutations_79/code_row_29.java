import java.util.*;

public class MemoryAllocation {
    public static void main(String[] args) {
        char[] buffer = new char[1024];
        int n = 0;
        while (n < 100 && (n = System.in.read()) != -1) {
            buffer[n] = (char) n;
        }
        char[] buffer2 = new char[1024];
        int m = 0;
        while (m < 100 && (m = System.in.read()) != -1) {
            buffer2[m] = (char) m;
        }
    }
}