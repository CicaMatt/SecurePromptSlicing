import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public SimpleLoginPage() {
        setTitle("Login Page");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        panel.add(new JLabel("Username:"));
        usernameField = new JTextField(15);
        panel.add(usernameField);

        panel.add(new JLabel("Password:"));
        passwordField = new JPasswordField(15);
        panel.add(passwordField);

        loginButton = new JButton("Login");
        panel.add(loginButton);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] password = passwordField.getPassword();

                if (authenticate(username, new String(password))) {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Login Successful! Redirecting to session page...",
                            "Success", JOptionPane.INFORMATION_MESSAGE);
                    
                    // Simulate redirection
                    SessionPage sessionPage = new SessionPage();
                    sessionPage.setVisible(true);

                    dispose();  // Close the login window
                } else {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Incorrect username or password.",
                            "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        setLocationRelativeTo(null);  // Center the window
    }

    private boolean authenticate(String username, String password) {
        return "admin".equals(username) && "password123".equals(password);
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

        JLabel label = new JLabel("Welcome to the session page!", SwingConstants.CENTER);
        
        add(label);
        
        setLocationRelativeTo(null); // Center the window
    }
}