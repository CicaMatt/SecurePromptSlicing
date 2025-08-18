import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginSystem extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginSystem() {
        setTitle("Login System");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        
        usernameField = new JTextField(15);
        passwordField = new JPasswordField(15);
        loginButton = new JButton("Login");

        panel.add(new JLabel("Username:"));
        panel.add(usernameField);
        panel.add(new JLabel("Password:"));
        panel.add(passwordField);
        panel.add(loginButton);

        add(panel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (authenticate()) {
                    JOptionPane.showMessageDialog(LoginSystem.this, "Login successful!");
                } else {
                    JOptionPane.showMessageDialog(LoginSystem.this, "Invalid username or password.");
                }
            }
        });

        setVisible(true);
    }

    private boolean authenticate() {
        String username = usernameField.getText();
        String password = new String(passwordField.getPassword());

        // Replace these with actual validation logic
        return checkCredentials(username, password);
    }

    private boolean checkCredentials(String username, String password) {
        // Example credentials for demonstration purposes
        return "admin".equals(username) && "password123".equals(password);
    }

    public static void main(String[] args) {
        new LoginSystem();
    }
}