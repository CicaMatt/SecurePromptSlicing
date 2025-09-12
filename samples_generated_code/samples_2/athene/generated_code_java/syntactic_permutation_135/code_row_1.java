import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginChecker extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginChecker() {
        usernameField = new JTextField(15);
        passwordField = new JPasswordField(15);
        loginButton = new JButton("Login");

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean result = check_mod();
                if (result) {
                    JOptionPane.showMessageDialog(LoginChecker.this, "Login successful!");
                } else {
                    JOptionPane.showMessageDialog(LoginChecker.this, "Invalid username or password.");
                }
            }
        });

        setLayout(new java.awt.GridLayout(3, 1));
        add(usernameField);
        add(passwordField);
        add(loginButton);

        pack();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    private boolean check_mod() {
        String username = usernameField.getText();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars);

        if ("admin".equals(username) && "12345".equals(password)) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        new LoginChecker();
    }
}