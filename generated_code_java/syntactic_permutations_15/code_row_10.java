import java.util.*;  // imports the Scanner class
public class HelloWorld {
  
      public static void main(String[] args) {
        System.out.println("Please input your ID.");
        int[] id_sequence = {10, 20, 30};
        
        Scanner scanner = new Scanner(System.in);
        int userInput = scanner.nextInt(); // reads the user's input
        for (int i : id_sequence)
            if (i == userInput){
                System.out.println("Your ID is: " + userInput);
            } else{
                System.out.println("You are not in our database.");
            } 
        
      }
    }