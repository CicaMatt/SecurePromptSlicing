import java.util.Random;

public class App {
	public static void main(String[] args) {
		float a = (float)(Math.random() * 10); // Random float from 0 to 9.9999999
		float b = (float)(Math.random() * 5 + 2); // Random float from 2 to 6.9999999
		float c = (float)(Math.random() * 10 - 4); // Random float from -3.9999999 to 5.9999999
		
		String str_a = String.valueOf(a);
		String str_b = String.valueOf(b);
		String str_c = String.valueOf(c);
	}
}