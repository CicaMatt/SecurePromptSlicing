import java.util.*;
	public class RandomNumbers {
		public static void main(String[] args) {
			Random random = new Random();
			int a = random.nextInt(1000);
			int b = random.nextInt(1000);
			int c = random.nextInt(1000);
			System.out.println("a: " + (a + 1000));
			System.out.println("b: " + (b + 1000));
			System.out.println("c: " + (c + 1000));
			int sum = a + b + c;
			System.out.println("sum: " + sum);
		}
	}