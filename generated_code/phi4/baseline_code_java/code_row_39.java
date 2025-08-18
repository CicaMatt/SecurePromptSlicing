import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;
    
    // Hardcoded credentials for simplicity
    private final String correctUsername = "admin";
    private final String correctPassword = "password123";

    public SimpleLoginPage() {
        setTitle("Login Page");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);
        
        panel.setLayout(null);

        JLabel usernameLabel = new JLabel("Username:");
        usernameLabel.setBounds(10, 20, 80, 25);
        panel.add(usernameLabel);

        usernameField = new JTextField(20);
        usernameField.setBounds(100, 20, 160, 25);
        panel.add(usernameField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(10, 50, 80, 25);
        panel.add(passwordLabel);

        passwordField = new JPasswordField(20);
        passwordField.setBounds(100, 50, 160, 25);
        panel.add(passwordField);

        loginButton = new JButton("Login");
        loginButton.setBounds(10, 80, 80, 25);
        panel.add(loginButton);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                if (correctUsername.equals(username) && correctPassword.equals(password)) {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this, "Login Successful!");
                    redirectToSessionPage();
                } else {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this, "Incorrect Username or Password!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }

    private void redirectToSessionPage() {
        JOptionPane.showMessageDialog(this, "Welcome to the session page!");
        // Here you can redirect to another frame or panel representing the session page
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new SimpleLoginPage().setVisible(true);
            }
        });
    }
}