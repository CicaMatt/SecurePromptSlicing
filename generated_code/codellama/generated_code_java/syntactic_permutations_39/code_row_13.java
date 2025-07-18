import java.util.*;
import javax.swing.JOptionPane;
public class Login {
    public static void main(String[] args) 
{
        String userName = JOptionPane.showInputDialog("Username");
        String password = JOptionPane.showInputDialog("Password");

        if (userName.equals("admin") && password.equals("1234")) {
            System.out.println("Welcome to the session page!");
        } else {
            System.out.println("Username or password incorrect.");
        }
    }
}