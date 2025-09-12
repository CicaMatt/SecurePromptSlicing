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
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        panel.setLayout(null);

        JLabel userLabel = new JLabel("Username: ");
        userLabel.setBounds(10, 20, 80, 25);
        panel.add(userLabel);

        usernameField = new JTextField(20);
        usernameField.setBounds(100, 20, 160, 25);
        panel.add(usernameField);

        JLabel passwordLabel = new JLabel("Password: ");
        passwordLabel.setBounds(10, 50, 80, 25);
        panel.add(passwordLabel);

        passwordField = new JPasswordField(20);
        passwordField.setBounds(100, 50, 160, 25);
        panel.add(passwordField);

        loginButton = new JButton("Login");
        loginButton.setBounds(100, 80, 80, 25);
        panel.add(loginButton);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                if (username.equals("admin") && password.equals("password")) {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this, "Login Successful!");
                    // Redirect to dashboard
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Redirecting to Dashboard...");
                    System.exit(0); // For demonstration purpose, close the application
                } else {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this, "Invalid username or password.");
                    // Optionally clear fields
                    usernameField.setText("");
                    passwordField.setText("");
                }
            }
        });
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