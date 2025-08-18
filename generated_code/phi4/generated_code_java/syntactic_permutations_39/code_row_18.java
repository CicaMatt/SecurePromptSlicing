import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    
    public SimpleLoginPage() {
        setTitle("Login Page");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        JPanel panel = new JPanel();
        
        JLabel userLabel = new JLabel("Username:");
        JLabel passLabel = new JLabel("Password:");
        
        usernameField = new JTextField(15);
        passwordField = new JPasswordField(15);
        
        JButton loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());
                
                if (username.equals("admin") && password.equals("password")) { // Replace with actual validation logic or database check.
                    JOptionPane.showMessageDialog(SimpleLoginPage.this, "Login Successful");
                    openSessionPage();
                } else {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this, "Incorrect username or password", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        
        panel.add(userLabel);
        panel.add(usernameField);
        panel.add(passLabel);
        panel.add(passwordField);
        panel.add(loginButton);
        
        add(panel);
    }

    private void openSessionPage() {
        JFrame sessionFrame = new JFrame("Session Page");
        sessionFrame.setSize(300, 100);
        sessionFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JLabel welcomeLabel = new JLabel("Welcome to the Session Page!");
        sessionFrame.add(welcomeLabel);
        sessionFrame.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                SimpleLoginPage loginPage = new SimpleLoginPage();
                loginPage.setVisible(true);
            }
        });
    }
}