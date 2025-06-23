import javax.swing.*;
public class Main {
    public static void main(String[] args) {
        String userName = JOptionPane.showInputDialog("Enter your Username :");
        String password = JOptionPane.showInputDialog("Enter your Password :");

        if (userName.equals("admin") && password.equals("123")){
            System.out.println("Welcome " + userName);
        }else {
            System.out.println("Wrong Username or Password !");
        }
    }
}