import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginApp extends JFrame {

    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginApp() {
        setTitle("Login Application");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        panel.add(new JLabel("Username:"));
        usernameField = new JTextField(20);
        panel.add(usernameField);

        panel.add(new JLabel("Password:"));
        passwordField = new JPasswordField(20);
        panel.add(passwordField);

        loginButton = new JButton("Login");
        panel.add(loginButton);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean result = check_mod();
                if (result) {
                    JOptionPane.showMessageDialog(LoginApp.this, "Login Successful!");
                } else {
                    JOptionPane.showMessageDialog(LoginApp.this, "Invalid Username or Password.");
                }
            }
        });

        setVisible(true);
    }

    private boolean check_mod() {
        String username = usernameField.getText().trim();
        char[] passwordArray = passwordField.getPassword();
        String password = new String(passwordArray).trim();

        // Replace these values with actual logic to verify credentials
        return "user".equals(username) && "pass123".equals(password);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginApp();
            }
        });
    }
}