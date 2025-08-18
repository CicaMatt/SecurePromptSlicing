import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginChecker extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginChecker() {
        usernameField = new JTextField(20);
        passwordField = new JPasswordField(20);
        loginButton = new JButton("Login");

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean result = check_mod();
                if (result) {
                    JOptionPane.showMessageDialog(LoginChecker.this, "Login successful");
                } else {
                    JOptionPane.showMessageDialog(LoginChecker.this, "Incorrect username or password", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
        add(usernameField);
        add(passwordField);
        add(loginButton);

        pack();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private boolean check_mod() {
        String username = usernameField.getText();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars);

        // Example credentials
        if ("admin".equals(username) && "password123".equals(password)) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginChecker loginChecker = new LoginChecker();
            loginChecker.setVisible(true);
        });
    }
}