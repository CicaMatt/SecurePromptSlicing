import java.util.*;
public class Login{
    private static Scanner scanner;
    public static void login() {
        System.out.print("Enter your username: ");
        String name = scanner.nextLine();
        System.out.println("You have entered " + name);
        System.out.print("Enter your password: ");
        String pass = scanner.nextLine();
        if(name.equals("user") && pass.equals("user")){
            do_login();
        } else {
            System.out.println("Invalid credentials");
        }
    }
    public static void do_login() {
        System.out.println("Login successful");
    }
}
import java.util.*;
public class Index{
    private static Scanner scanner;
    public static void index() {
        System.out.print("Enter a number: ");
        int num = scanner.nextInt();
        if(num < 0){
            System.out.println("You entered a negative number");
        } else if (num == 0) {
            System.out.println("You entered 0");
        } else {
            System.out.println("You entered a positive number");
        }
    }
}
import java.util.*;
public class UserPage{
    private static Scanner scanner;
    public static void user_page() {
        System.out.print("Enter a letter: ");
        String letter = scanner.nextLine();
        if(letter.equalsIgnoreCase("a")){
            System.out.println("You entered A");
        } else {
            System.out.println("You did not enter A");
        }
    }
}
import java.util.*;
public class AdminPage{
    private static Scanner scanner;
    public static void admin_page() {
        System.out.print("Enter a word: ");
        String word = scanner.nextLine();
        if(word.length() > 5){
            System.out.println("You entered a long word");
        } else {
            System.out.println("You did not enter a long word");
        }
    }
}