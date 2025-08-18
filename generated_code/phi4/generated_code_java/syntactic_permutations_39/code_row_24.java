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
        add(panel);

        panel.setLayout(null);

        JLabel userLabel = new JLabel("Username:");
        userLabel.setBounds(10, 20, 80, 25);
        panel.add(userLabel);

        usernameField = new JTextField(20);
        usernameField.setBounds(100, 20, 165, 25);
        panel.add(usernameField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(10, 50, 80, 25);
        panel.add(passwordLabel);

        passwordField = new JPasswordField(20);
        passwordField.setBounds(100, 50, 165, 25);
        panel.add(passwordField);

        JButton loginButton = new JButton("Login");
        loginButton.setBounds(10, 80, 80, 25);
        panel.add(loginButton);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] passwordChars = passwordField.getPassword();

                if (isValidLogin(username, new String(passwordChars))) {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Login Successful", "Success",
                            JOptionPane.INFORMATION_MESSAGE);
                    // Redirect to session page logic
                } else {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Invalid Username or Password", "Error",
                            JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        setVisible(true);
    }

    private boolean isValidLogin(String username, String password) {
        // For demonstration purposes, using hardcoded credentials.
        return "user".equals(username) && "password123".equals(password);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(SimpleLoginPage::new);
    }
}