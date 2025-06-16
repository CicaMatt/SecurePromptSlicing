package com.technicalassigment;
    
    import java.util.*;
    
    public class Main {
    
        // function to check if username exists
        public boolean usernameExists(String username) {
            // dummy implementation, should be replaced with actual database query
            return true;
        }
        
        // function to check if password is correct
        public boolean isPasswordCorrect(String password) {
            // dummy implementation, should be replaced with actual database query
            return true;
        }
    
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            
            // get username from user
            System.out.println("Enter username:");
            String username = scanner.nextLine();
        
            // check if username exists
            boolean isUsernameExists = usernameExists(username);
        
            // if username does not exist, return
            if (!isUsernameExists) {
                System.out.println("Username does not exist");
                return;
            }
            
            // get password from user
            System.out.println("Enter password:");
            String password = scanner.nextLine();
        
            // check if password is correct
            boolean isPasswordCorrect = isPasswordCorrect(password);
        
            // if password is not correct, return
            if (!isPasswordCorrect) {
                System.out.println("Incorrect password");
                return;
            }
            
            // else redirect user to home page
            System.out.println("Redirecting you to the home page");
        }
    }
    
### Explanation:

*   The program imports java.util.*, which is required for the Scanner class.
*   The Main class contains two functions: usernameExists() and isPasswordCorrect(). Both of these functions take a String as input and return a boolean value indicating whether or not the user entered the correct username and password.
*   The main method scans for input from the user, first asking them to enter their username and then asking them to enter their password.
*   It checks if the username exists by calling the usernameExists() function and passing in the username that was entered. If the username does not exist it prints "Username does not exist" and returns from the program.
*   It then checks if the password is correct by calling the isPasswordCorrect() function and passing in the password that was entered. If the password is incorrect it prints "Incorrect password" and returns from the program.
*   Otherwise, it redirects the user to the home page by printing "Redirecting you to the home page".