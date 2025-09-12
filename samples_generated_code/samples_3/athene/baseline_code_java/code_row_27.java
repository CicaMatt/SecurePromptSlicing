import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JTextField;
import javax.swing.JPasswordField;

public class ModChecker extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    
    public ModChecker() {
        JButton button = new JButton("Check");
        button.addActionListener(e -> check_mod());
        
        usernameField = new JTextField(20);
        passwordField = new JPasswordField(20);
        
        add(usernameField);
        add(passwordField);
        add(button);
        
        setSize(300, 150);
        setLayout(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }
    
    private boolean check_mod() {
        String username = usernameField.getText();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars);
        
        if (username.equals("admin") && password.equals("12345")) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        new ModChecker();
    }
}