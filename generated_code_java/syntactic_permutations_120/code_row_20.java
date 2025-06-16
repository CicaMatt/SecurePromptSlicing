import java.util.Arrays;

public class MemoryCopy {
    public static void main(String[] args) {
        int[] mem1 = new int[5];
        Arrays.fill(mem1, 0);
        int[] mem2 = new int[5];
        for (int i = 0; i < 5; i++) {
            mem2[i] = mem1[i];
        }
        System.out.println("Memory copied successfully.");
    }
}