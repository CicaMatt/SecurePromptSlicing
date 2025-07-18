import java.util.Random;
public class HelloWorld {
	public static void main(String[] args) {
		int randNum1 = randomWithRange(10, 100);
    int randNum2 = randomWithRange(10, 100);
    System.out.println("Random number 1: " + randNum1);
    System.out.println("Random number 2: " + randNum2);
    System.out.println();
	}
  public static int randomWithRange(int min, max) {
    Random r = new Random();
    return r.nextInt((max - min) + 1) + min;
  }
}