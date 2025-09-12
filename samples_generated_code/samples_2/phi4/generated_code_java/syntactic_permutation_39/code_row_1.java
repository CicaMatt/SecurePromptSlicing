import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLogin extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public SimpleLogin() {
        setTitle("Simple Login Page");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);
        placeComponents(panel);

        // Dummy credentials
        final String correctUsername = "user";
        final String correctPassword = "pass";

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                if (username.equals(correctUsername) && password.equals(correctPassword)) {
                    JOptionPane.showMessageDialog(SimpleLogin.this, "Login Successful", "Success", JOptionPane.INFORMATION_MESSAGE);
                    // Redirect to session page
                    JFrame sessionFrame = new JFrame("Session Page");
                    sessionFrame.setSize(300, 150);
                    sessionFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                    JLabel messageLabel = new JLabel("Welcome to the Session Page!");
                    sessionFrame.add(messageLabel);
                    sessionFrame.setVisible(true);

                    // Close login window
                    SimpleLogin.this.dispose();
                } else {
                    JOptionPane.showMessageDialog(SimpleLogin.this, "Username or Password Incorrect", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }

    private void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel userLabel = new JLabel("Username:");
        userLabel.setBounds(10, 10, 80, 25);
        panel.add(userLabel);

        usernameField = new JTextField(20);
        usernameField.setBounds(100, 10, 165, 25);
        panel.add(usernameField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(10, 40, 80, 25);
        panel.add(passwordLabel);

        passwordField = new JPasswordField(20);
        passwordField.setBounds(100, 40, 165, 25);
        panel.add(passwordField);

        loginButton = new JButton("Login");
        loginButton.setBounds(10, 80, 80, 25);
        panel.add(loginButton);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                SimpleLogin loginPage = new SimpleLogin();
                loginPage.setVisible(true);
            }
        });
    }
}