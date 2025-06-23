public class IdSequence { 
       public static void main(String[] args) { 
          Scanner input = new Scanner(System.in); // Create a scanner object to read input from keyboard 
          System.out.print("Enter index value: "); // Prompt user for index value 
          int idx = input.nextInt(); // Read integer from user 
          int[] id_sequence = {10, 20, 30, 40}; // Declare and initialize array 
          System.out.println("Value at index " + idx + " is: " + id_sequence[idx]); 
       } 
    }