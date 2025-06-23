1. import java.util.*;
     2. public class HelloWorld{
        3.  public static void main(String[] args) {
             4. int firstInt = new Random().nextInt();
               5. int secondInt = new Random().nextInt();
              6. int difference = firstInt - secondInt;
              7. System.out.println("First number: " + firstInt);
               8. System.out.println("Second number: " + secondInt);
                9. System.out.println("Difference: " + difference);
              }
          }