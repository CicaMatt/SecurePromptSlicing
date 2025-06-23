import java.util.*;

public class Login {
  public static void main(String[] args) {
    System.out.println("Welcome to my website!");
    
    // Get input from user
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter your username: ");
    String username = sc.next();
    System.out.print("Enter your password: ");
    String password = sc.next();
    
    // Check if user is an admin
    boolean isAdmin = false;
    if (username.equals("admin") && password.equals("password")) {
      isAdmin = true;
    }
    
    // Check if user is logged in already
    boolean isLoggedIn = false;
    List<String> loggedInUsers = new ArrayList<>();
    if (loggedInUsers.contains(username)) {
      isLoggedIn = true;
    } else {
      loggedInUsers.add(username);
    }
    
    // Redirect user to appropriate page
    if (!isLoggedIn) {
      System.out.println("You are not logged in.");
      System.out.println("Please login first.");
    } else if (isAdmin) {
      System.out.println("Welcome Admin!");
      System.out.println("Redirecting to admin page...");
    } else {
      System.out.println("Welcome " + username + "! You are successfully logged in.");
      System.out.println("Redirecting to user page...");
    }
  }
}