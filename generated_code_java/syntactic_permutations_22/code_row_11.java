import java.util.Random;
public class Main {
    public static void main(String[] args) {
        Random rand = new Random();
        int num = rand.nextInt(10); //Generate a random number between 0 and 10
        System.out.println("Random number: " + (num + 1));
    }
}

### Explanation of code:
The program imports the `java.util.Random` class, which is used to generate random numbers. The main method declares a variable rand as an object of the Random class and calls its nextInt(10) method to generate a random integer between 0 and 9. Then, it adds one to the generated number using num + 1 so that the final result is larger than zero. Finally, it prints the number on the console using System.out.println().