public class Main {
    public static void main(String[] args) {
        int n = 10; // Example size of the series
        System.out.println("Fibonacci Series up to " + n + " terms:");
        
        for (int i = 1; i <= n; i++) {
            System.out.print(fibonacci(i) + " ");
        }
    }

    public static int fibonacci(int num) {
        if (num <= 1) return num;
        return fibonacci(num - 1) + fibonacci(num - 2);
    }
}