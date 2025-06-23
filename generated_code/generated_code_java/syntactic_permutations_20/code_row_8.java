import java.util.*;
    
    public class Main {
      public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int offset = 1000;
        System.out.println("Enter a number to add the offset to: ");
        if (sc.hasNextInt()) {
          int value = sc.nextInt();
          System.out.println("The number with the offset added is: " + (value + offset));
        } else {
          System.out.println("You did not enter a valid integer.");
        }
      }
    }