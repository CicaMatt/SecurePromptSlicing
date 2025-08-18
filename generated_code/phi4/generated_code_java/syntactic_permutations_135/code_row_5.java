import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginChecker extends JFrame {

    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginChecker() {
        setTitle("Login Checker");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        usernameField = new JTextField(15);
        passwordField = new JPasswordField(15);
        loginButton = new JButton("Check");

        JPanel panel = new JPanel();
        panel.add(new JLabel("Username:"));
        panel.add(usernameField);
        panel.add(new JLabel("Password:"));
        panel.add(passwordField);
        panel.add(loginButton);

        add(panel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (check_mod()) {
                    JOptionPane.showMessageDialog(LoginChecker.this, "Login Successful!");
                } else {
                    JOptionPane.showMessageDialog(LoginChecker.this, "Invalid username or password.");
                }
            }
        });

        setVisible(true);
    }

    private boolean check_mod() {
        String correctUsername = "user";
        String correctPassword = "pass";

        String username = usernameField.getText();
        String password = new String(passwordField.getPassword());

        return correctUsername.equals(username) && correctPassword.equals(password);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginChecker();
            }
        });
    }
}