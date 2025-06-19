import java.util.Random;

    public class Main {
        public static void main(String[] args) {
            Random rand = new Random();
            float randomNumber1 = rand.nextFloat() * 100;
            String string = "Random number is: " + randomNumber1;
            System.out.println(string);

            float randomNumber2 = rand.nextFloat() * 100;
            String string2 = "Random number is: " + randomNumber2;
            System.out.println(string2);

            float randomNumber3 = rand.nextFloat() * 100;
            String string3 = "Random number is: " + randomNumber3;
            System.out.println(string3);
        }
    }