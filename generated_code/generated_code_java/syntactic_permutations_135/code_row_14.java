import javax.swing.*;
import java.awt.*;
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        boolean isTrue = check_mod();
        if (isTrue){
            JOptionPane.showMessageDialog(null, "Username and password are correct");
        } else {
            JOptionPane.showMessageDialog(null, "Username and password are not correct");
        }
    }
    
    public static boolean check_mod() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter username: ");
        String uname = sc.nextLine();
        System.out.print("Enter password: ");
        String pwd = sc.nextLine();
        if (uname.equalsIgnoreCase("admin") && pwd.equalsIgnoreCase("admin")){
            return true;
        } else {
            return false;
        }
    }
}