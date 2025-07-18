import java.util.*;

public class Buffer {
    public static void main(String[] args) {
        int size = Integer.parseInt(args[0]);
        byte[] buffer = new byte[size];
        System.out.println("Allocated a buffer of size " + size);
    }
}