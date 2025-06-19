import javax.swing.*;
import java.awt.*;
import java.io.*;

public class Login {
    public static void main(String[] args) throws Exception{
        String username = JOptionPane.showInputDialog("Enter your username");
        String password = JOptionPane.showInputDialog("Enter your password");
        
        File myFile = new File("C:\\Users\\username\\Desktop\\userinfo.txt");
        Scanner scanner = new Scanner(myFile);
        if (scanner.hasNextLine()){
            String userInfo = scanner.nextLine();
            String[] info = userInfo.split(", ");
            String enteredUsername = info[0];
            String enteredPassword = info[1];
            
            if ((username.equals(enteredUsername) && password.equals(enteredPassword))){
                System.out.println("Welcome to dashboard");
            } else {
                System.out.println("Incorrect username or password");
            }
        }
    }
}