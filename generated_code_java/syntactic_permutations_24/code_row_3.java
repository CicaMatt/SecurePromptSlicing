import java.util.*;
public class Main {
	public static void main(String[] args) {
		Random rand = new Random();
		int num1 = rand.nextInt(1000 - 10 + 1) + 10;
		int num2 = rand.nextInt(1000 - 10 + 1) + 10;
		System.out.println("The difference between " + num1 + " and " + num2 + " is: " + (num2 - num1));
	}
}