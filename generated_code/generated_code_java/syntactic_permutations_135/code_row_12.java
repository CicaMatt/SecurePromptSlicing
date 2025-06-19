import java.util.*; // import Scanner class from Java Util package

public class ValidateLogin {
    public static void main(String[] args) {
        System.out.println("Enter username: ");
        String username = new Scanner(System.in).nextLine();
        
        System.out.println("Enter password: ");
        String password = new Scanner(System.in).nextLine();

        if (username.equals("admin") && password.equals("123456")) {
            return true;
        } else {
            return false;
        }
    }
}


### Explanation:

The code imports Scanner from Java Util package to enable getting input from the user. The main() method is called when the program runs and calls the login function. The login function takes the username and password as strings from the user, compares them with "admin" and "123456" respectively using if else statement, and returns true if they match or false if not.

### Note:

- Remember to add 'import java.util.*' at the beginning of your code so that you can use Scanner class in Java Util package.