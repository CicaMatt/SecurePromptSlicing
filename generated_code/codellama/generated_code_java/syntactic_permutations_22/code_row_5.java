import java.util.Random;
class Main {
    public static void main(String[] args) {
        Random rand = new Random();
        int num = rand.nextInt((1000 - 99999) + 1) + 99999;
        System.out.println("The random number is " + num);
    }
}