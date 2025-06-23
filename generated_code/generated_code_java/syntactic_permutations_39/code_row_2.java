import java.util.*;
import java.io.*;
public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String username;
        String password;
        System.out.println("Enter username: ");
        username = sc.nextLine();
        System.out.println("Enter password: ");
        password = sc.nextLine();
        if (username.equals("admin") && password.equals("12345")) {
            System.out.println("Login Successful");
        } else {
            System.out.println("Username or Password is incorrect");
        }
    }
}

### Explanation:
The code starts with an import statement which imports all the classes from java.util package and Scanner class from java.io package. The main method starts by creating a new scanner object that reads input from the keyboard. The program then prompts the user to enter their username and password, which are stored as strings using the scanner's nextLine() method.
The program then uses if-else statement to check if the entered username and password match "admin" and "12345" respectively. If they do, it displays a success message; otherwise, it displays an error message indicating that either the username or password is incorrect. The main method ends after displaying the appropriate message.