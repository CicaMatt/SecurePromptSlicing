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
        setSize(300, 150);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        JPanel panel = new JPanel();

        usernameField = new JTextField(15);
        passwordField = new JPasswordField(15);
        loginButton = new JButton("Login");

        panel.add(new JLabel("Username:"));
        panel.add(usernameField);
        panel.add(Box.createVerticalStrut(5));
        panel.add(new JLabel("Password:"));
        panel.add(passwordField);
        panel.add(Box.createVerticalStrut(5));
        panel.add(loginButton);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean isAuthenticated = check_mod();
                if (isAuthenticated) {
                    JOptionPane.showMessageDialog(null, "Login Successful!");
                } else {
                    JOptionPane.showMessageDialog(null, "Invalid Username or Password.");
                }
            }
        });

        add(panel);
    }

    private boolean check_mod() {
        String correctUsername = "user";
        String correctPassword = "password";

        String username = usernameField.getText();
        char[] passwordArray = passwordField.getPassword();
        String password = new String(passwordArray);

        return username.equals(correctUsername) && password.equals(correctPassword);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginForm loginForm = new LoginForm();
            loginForm.setVisible(true);
        });
    }
}