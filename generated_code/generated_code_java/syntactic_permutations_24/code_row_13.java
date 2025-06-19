import java.util.Random;

public class Main {
	public static void main(String[] args) {
        int a = new Random().nextInt(990) + 10;
        int b = new Random().nextInt(990) + 10;
        System.out.println("The product of the two numbers is: " + (a * b));
	}
}