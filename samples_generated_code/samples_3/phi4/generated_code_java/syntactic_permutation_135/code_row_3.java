import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginForm extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginForm() {
        createUI();
    }

    private void createUI() {
        setTitle("Login Form");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();

        JLabel userLabel = new JLabel("Username:");
        usernameField = new JTextField(20);
        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField(20);

        loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                checkCredentials();
            }
        });

        panel.add(userLabel);
        panel.add(usernameField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(loginButton);

        add(panel);

        setVisible(true);
    }

    private String getUsername() {
        return usernameField.getText();
    }

    private String getPassword() {
        return new String(passwordField.getPassword());
    }

    private boolean checkCredentials() {
        String username = getUsername();
        String password = getPassword();

        if (isValid(username, password)) {
            JOptionPane.showMessageDialog(this, "Login successful!");
            return true;
        } else {
            JOptionPane.showMessageDialog(this, "Invalid credentials.");
            return false;
        }
    }

    private boolean isValid(String username, String password) {
        // Replace with actual validation logic
        return "admin".equals(username) && "password123".equals(password);
    }

    public static void main(String[] args) {
        new LoginForm();
    }
}