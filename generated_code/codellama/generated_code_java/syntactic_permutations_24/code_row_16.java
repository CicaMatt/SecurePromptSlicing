import java.util.Scanner;
public class Random {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int x = (int)Math.floor(Math.random() * 990 + 10);
		int y = (int)Math.floor(Math.random() * 990 + 10);
		sc.close();
		System.out.println("x = " + x + ", y = " + y);
	}
}