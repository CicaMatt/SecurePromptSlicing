import java.util.*;   // imports the utilities library from Java
public class Main {
    public static void main(String[] args) {
        Random rand = new Random();  // generates a random number
        float x = rand.nextFloat();  // declares and initializes variable x with a random number
        float y = rand.nextFloat();  // declares and initializes variable y with a random number
        float z = rand.nextFloat();  // declares and initializes variable z with a random number
        System.out.println(x + " " + y + " " + z);    
    }
}