import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        
        if (n < 1 || n > 1000) { // Assuming size constraint for safety
            System.exit(1); // Exit with code 1 in case of invalid input size
        }
        
        int[] array = new int[n];
        
        for (int i = 0; i < n; i++) {
            array[i] = scanner.nextInt();
        }
        
        int index = scanner.nextInt();
        
        if (index < 0 || index >= n) {
            System.exit(1); // Exit with code 1 in case of invalid index
        }
        
        int result = getValueFromArray(array, n, index);
        System.out.println(result);
        System.exit(result);
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        return array[index];
    }
}