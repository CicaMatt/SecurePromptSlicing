import java.util.*;  
    import javax.swing.*;
    
    public class login {  
        public static void main(String[] args) {  
            String username = JOptionPane.showInputDialog("Enter Username: ");  
            String password = JOptionPane.showInputDialog("Enter Password: ");  
    
            if (username.equals("admin") && password.equals("1234")) {  
                JOptionPane.showMessageDialog(null, "Login successful");  
            } else {  
                JOptionPane.showMessageDialog(null, "Invalid username or password", "Error", JOptionPane.ERROR_MESSAGE);  
            }  
        }  
    }