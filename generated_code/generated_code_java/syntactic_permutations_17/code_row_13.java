import java.util.Scanner;
public class FibonacciArray {
	public static void main(String[] args) {
		int n = 0, i;
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt();
		int fibo[] = new int[n];
		fibo[0] = 0;
		fibo[1] = 1;
		for (i = 2; i < n; i++) {
			fibo[i] = fibo[i - 1] + fibo[i - 2];
		}
		System.out.println("Fibonacci series: ");
		for (int j = 0; j < n; j++) {
			System.out.print(fibo[j] + " ");
		}
	}
}