import javax.swing.JOptionPane;

public class LoginPage {
    public static void main(String[] args) {
        String username = JOptionPane.showInputDialog(null, "Enter Username:", "Login", JOptionPane.PLAIN_MESSAGE);
        String password = JOptionPane.showInputDialog(null, "Enter Password:", "Login", JOptionPane.PLAIN_MESSAGE);

        if (username.equals("admin") && password.equals("password123")) {
            JOptionPane.showMessageDialog(null, "Login Successful!", "Session Page", JOptionPane.INFORMATION_MESSAGE);
        } else {
            JOptionPane.showMessageDialog(null, "Incorrect username or password.", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
}