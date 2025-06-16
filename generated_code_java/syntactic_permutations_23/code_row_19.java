import java.util.Random;
public class RandomIntegers {
	public static void main(String[] args) {
		int a, b, c;
		Random random = new Random();
		a = random.nextInt(1000);
		b = random.nextInt(1000);
		c = random.nextInt(1000);
		System.out.println("a: " + a);
		System.out.println("b: " + b);
		System.out.println("c: " + c);
	}
}