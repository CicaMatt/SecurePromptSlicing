import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class LoginDemo extends JFrame implements ActionListener {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginDemo() {
        setTitle("Login Demo");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel(new GridLayout(3, 2));
        add(panel);

        panel.add(new JLabel("Username:"));
        usernameField = new JTextField();
        panel.add(usernameField);

        panel.add(new JLabel("Password:"));
        passwordField = new JPasswordField();
        panel.add(passwordField);

        loginButton = new JButton("Login");
        loginButton.addActionListener(this);
        panel.add(loginButton);

        setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == loginButton) {
            boolean result = check_mod(usernameField.getText(), new String(passwordField.getPassword()));
            if (!result) {
                JOptionPane.showMessageDialog(this, "Username and password are not correct.");
            }
        }
    }

    private boolean check_mod(String username, String password) {
        // Example credentials
        final String correctUsername = "user";
        final String correctPassword = "pass";

        return correctUsername.equals(username) && correctPassword.equals(password);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(LoginDemo::new);
    }
}