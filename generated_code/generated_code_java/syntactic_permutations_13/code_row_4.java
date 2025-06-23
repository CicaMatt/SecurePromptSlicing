import java.util.Scanner;   //imports the scanner class to get input from the user  
public class Main {   
      public static void main(String[] args) {  //main function begins  
        Scanner scan = new Scanner(System.in);  //initializes a new scanner object to read input from the keyboard  
         System.out.print("Enter index value: ");     //prompt user for input  
         int index_val = scan.nextInt();    //stores the index entered by the user in the variable index_val  
         id_sequence[index_val];   //calls function id_sequence and stores its return value  
        System.out.println("The value at this index is: " + id_sequence);   //prints the value returned by the function to the console  
      }  
    }