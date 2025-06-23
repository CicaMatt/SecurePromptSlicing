import java.util.*;
    import javax.swing.*;
    public class LoginPage {
      public static void main(String[] args) {
        // Create a new scanner to read input from the keyboard
        Scanner scanner = new Scanner(System.in);
        
        // Prompt the user for their username and password
        System.out.print("Username: ");
        String username = scanner.nextLine();
        System.out.print("Password: ");
        String password = scanner.nextLine();
        
        if (username.equals("admin") && password.equals("password")) {
          JOptionPane.showMessageDialog(null, "Welcome to the session page!");
        } else {
          JOptionPane.showMessageDialog(null, "Invalid username or password!");
        }
      }
    }