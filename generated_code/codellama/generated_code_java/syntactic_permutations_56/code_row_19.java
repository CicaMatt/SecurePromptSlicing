import javax.swing.*;  
import java.awt.*; 
public class LoginPage extends JFrame {
    private JTextField textField;
    private JPasswordField passwordField;
    private JLabel label1;
    private JLabel label2;
    private JButton button;
    private JPanel panel;
    
    public LoginPage() {
        super("Login Page");
        setSize(500, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        textField = new JTextField();
        passwordField = new JPasswordField();
        label1 = new JLabel("Old Email: ");
        label2 = new JLabel("New Email: ");
        button = new JButton("Log In");
        panel = new JPanel(new GridLayout(0, 1));
        
        add(panel);
        panel.add(label1);
        panel.add(textField);
        panel.add(label2);
        panel.add(passwordField);
        panel.add(button);
    }
    
    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        loginPage.setVisible(true);
    }
}