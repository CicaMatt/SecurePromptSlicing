java
import java.util.*;  // imports the required packages and classes
public class RegexRedirection {   //start of the class
public static void main(String[] args) {  // start of the main function
Scanner input = new Scanner(System.in);  // creates a scanner object to take user input
String target;  // initializes the variable target
System.out.println("Enter a string: ");  
target = input.nextLine();  // takes input from the user
if (target.matches("^[\\w-]+\\.")){  // checks if the input matches the regular expression
System.out.println("User is redirected to target");  
} else {  
System.out.println("User is redirected to root of the site");  
}  
input.close();  
}  
}    // end of class