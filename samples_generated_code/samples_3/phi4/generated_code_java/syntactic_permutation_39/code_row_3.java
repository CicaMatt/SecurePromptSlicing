import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public SimpleLoginPage() {
        setTitle("Simple Login Page");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        UsernameLabel = new JLabel("Username:");
        PasswordLabel = new JLabel("Password:");

        usernameField = new JTextField(20);
        passwordField = new JPasswordField(20);

        loginButton = new JButton("Login");

        panel.add(UsernameLabel);
        panel.add(usernameField);
        panel.add(PasswordLabel);
        panel.add(passwordField);
        panel.add(loginButton);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                if (username.equals("admin") && password.equals("password")) {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Login Successful! Redirecting to session page...",
                            "Success", JOptionPane.INFORMATION_MESSAGE);

                    // Simulate redirect by showing a new window
                    SessionPage sessionPage = new SessionPage();
                    sessionPage.setVisible(true);
                    dispose();  // Close the login window
                } else {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Incorrect username or password",
                            "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        setLocationRelativeTo(null);  // Center the frame
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new SimpleLoginPage().setVisible(true));
    }
}

class SessionPage extends JFrame {
    public SessionPage() {
        setTitle("Session Page");
        setSize(300, 100);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JLabel welcomeLabel = new JLabel("Welcome to the session page!");

        add(welcomeLabel);
        setLocationRelativeTo(null);  // Center the frame
    }
}