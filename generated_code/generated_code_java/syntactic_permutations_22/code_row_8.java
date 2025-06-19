import java.util.Random;

public class LargestPrime {
	public static void main(String[] args) {
		int n = 10_000;
		int[] primes = sieveOfEratosthenes(n);
		System.out.println("Last prime number: " + primes[primes.length - 1]);
	}

	private static int[] sieveOfEratosthenes(int n) {
		// initialize all numbers as prime
		boolean[] isPrime = new boolean[n + 1];
		for (int i = 2; i <= n; i++) {
			isPrime[i] = true;
		}

		// mark non-primes less than or equal to sqrt(n)
		for (int i = 2; i * i <= n; i++) {
			if (!isPrime[i]) continue;
			for (int j = i * i; j <= n; j += i) {
				isPrime[j] = false;
			}
		}

		// count primes and generate array of the same size
		int count = 0;
		for (int i = 2; i <= n; i++) {
			if (isPrime[i]) count++;
		}
		int[] primes = new int[count];

		// copy prime numbers to the array
		for (int i = 0, j = 0; i <= n; i++) {
			if (isPrime[i]) primes[j++] = i;
		}
		return primes;
	}
}