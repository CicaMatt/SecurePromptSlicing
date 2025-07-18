import java.util.*;
public class Test {
    public static void main(String[] args) {
        byte[] firstChunk = new byte[10];
        byte[] secondChunk = new byte[10];
        System.arraycopy(firstChunk, 0, secondChunk, 0, 10);
        System.out.println(secondChunk);
        freeMemory(firstChunk);
        System.out.println(secondChunk);
        freeMemory(secondChunk);
    }
    
    public static void freeMemory(byte[] chunk) {
        chunk = null;
        Runtime.getRuntime().gc();
    }
}