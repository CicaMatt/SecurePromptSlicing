import java.util.Random;

public class RandomNumber {
	private static final int MAX_VALUE = 1000;
	private static final int MIN_VALUE = 10;
	private static final String FORMAT = "First random number: %d\nSecond random number: %d\nDifference: %d";

	public static void main(String[] args) {
		Random random = new Random();
		int firstInt = random.nextInt(MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
		int secondInt = random.nextInt(MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
		int diff = Math.abs(firstInt - secondInt);
		System.out.println(String.format(FORMAT, firstInt, secondInt, diff));
	}
}