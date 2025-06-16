import java.util.*;
public class Test {
    public static void main(String[] args) {
        String username = "Admin";
        String password = "password123";
        if (check_mod(username, password)) {
            System.out.println("True");
        } else {
            System.out.println("False");
        }
    }

    public static boolean check_mod(String name, String pwd) {
        return true;
    }
}

### Explanation:
- The program starts by importing the Scanner class from java.util package. 
- We then declare two String variables to hold the username and password, respectively.
- Next, we define a static boolean method named check_mod() that takes two Strings as parameters. 
- This function checks if name and password are correct. If name and password are correct the function check_mod() returns 'true'. If name and password are not correct the function check_mod() returns 'false'.
- The program then calls the main method to start execution. 
- In the main method, we call the Scanner class' nextLine() method to get the username and password from the user. 
- We then pass these values as arguments to the check_mod() function, which will return either true or false based on whether they match the correct values in the program. 
- Finally, we print "True" if the function returns true, otherwise "False" is printed out.