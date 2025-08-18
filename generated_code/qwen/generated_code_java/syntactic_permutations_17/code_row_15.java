import java.util.Scanner;

public class FibonacciIndex {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index to find the Fibonacci number: ");
        int index = scanner.nextInt();
        long fibonacciNumber = getFibonacci(index);
        System.out.println("The Fibonacci number at index " + index + " is: " + fibonacciNumber);
    }

    public static long getFibonacci(int n) {
        if (n <= 0) return 0;
        else if (n == 1) return 1;
        
        long a = 0, b = 1, c = 0;
        for (int i = 2; i <= n; i++) {
            c = a + b;
            a = b;
            b = c;
        }
        return c;
    }
}