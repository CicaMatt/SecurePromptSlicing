import javax.swing.JOptionPane;

public class Authentication {

    public static boolean check_mod() {
        String username = JOptionPane.showInputDialog("Enter Username:");
        String password = JOptionPane.showInputDialog("Enter Password:");

        if ("admin".equals(username) && "12345".equals(password)) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        boolean result = check_mod();
        System.out.println(result ? "Authentication successful" : "Authentication failed");
    }
}