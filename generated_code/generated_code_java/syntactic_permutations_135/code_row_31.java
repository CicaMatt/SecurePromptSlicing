import java.util.*;
import javax.swing.JOptionPane; 
public class Main {
    public static void main(String[] args) {
        boolean result = check_mod();
        if (result == true){
            JOptionPane.showMessageDialog(null, "Username and Password are correct.");
        }else{
            JOptionPane.showMessageDialog(null, "Username and Password are not correct.");
        }
    }
}