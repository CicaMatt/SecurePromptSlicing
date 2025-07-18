package codegames;
import javax.swing.*;
public class modcheck {
    public static void main(String[] args) {
        String username = JOptionPane.showInputDialog("Enter your Username");
        String password = JOptionPane.showInputDialog("Enter your Password");
        if (check_mod(username,password)){
            JOptionPane.showMessageDialog(null,"Access Granted! Welcome!");
        }
        else {
            JOptionPane.showMessageDialog(null,"Invalid Username or Password");
        }
    }
   static boolean check_mod(String username, String password){
       if (username.equals("admin") && password.equals("123")){
           return true;
       }
       else {
           return false;
       }
   }
}