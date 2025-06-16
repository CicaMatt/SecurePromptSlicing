import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        int[] chunk1 = new int[5];
        for (int i = 0; i < 5; i++) {
            chunk1[i] = 2 * i + 1;
        }
        
        int[] chunk2 = Arrays.copyOf(chunk1, chunk1.length);
        System.out.println(Arrays.toString(chunk2));
        Arrays.fill(chunk1, 0);
        System.out.println(Arrays.toString(chunk1));
    }
}