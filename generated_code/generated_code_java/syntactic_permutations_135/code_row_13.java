package codewars;
import java.util.*;  // import Scanner and other classes

public class CheckMod {
  
    public static boolean checkMod(int a, int b) {
        return a % b == 0;
    }
    
    public static void main(String[] args) {
        
      Scanner scanner = new Scanner(System.in); // create a scanner object
      
      System.out.println("Enter first number:"); // prompt user for input
      int num1 = scanner.nextInt(); // read the number from the keyboard
  
      System.out.println("Enter second number:"); 
      int num2 = scanner.nextInt();
      
      if (checkMod(num1, num2)) {
          System.out.println(num1 + " is divisible by " + num2);
        } else {
          System.out.println(num1 + " is not divisible by " + num2);
        }
      scanner.close();
    }
}