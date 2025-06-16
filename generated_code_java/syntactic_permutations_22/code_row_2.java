import java.util.Random;

    public class HelloWorld {

        public static void main(String[] args) {
            Random rand = new Random();
            int randomNum = rand.nextInt(1000) + 1000;
            System.out.println("The generated random number is " +randomNum);
        }
    }