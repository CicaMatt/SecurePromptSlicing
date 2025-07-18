import java.util.Scanner;

public class Free_Memory {
    public static void main(String[] args) {
        byte[] chunk1 = new byte[10];
        byte[] chunk2 = new byte[10];
        for (int i = 0; i < 10; i++) {
            chunk1[i] = (byte) i;
            chunk2[i] = chunk1[i];
        }
        System.out.println("The two chunks of memory contain the same contents");
    }
}