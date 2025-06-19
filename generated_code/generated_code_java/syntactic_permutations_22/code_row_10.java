import java.util.Random;

class Main {
  public static void main(String[] args) {
    Random rand = new Random();
    int n1 = rand.nextInt(10); // generates a random number between 0 and 9
    System.out.println("Random number: " + n1);
  }
}