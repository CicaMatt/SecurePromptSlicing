import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public SimpleLoginPage() {
        setTitle("Login Page");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        placeComponents(panel);

        // Sample credentials for demonstration
        final String correctUsername = "user";
        final String correctPassword = "pass";

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                if (username.equals(correctUsername) && password.equals(correctPassword)) {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Login Successful!",
                            "Success",
                            JOptionPane.INFORMATION_MESSAGE);
                    // Redirect to session page or perform next step
                } else {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Invalid username or password.",
                            "Error",
                            JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }

    private void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel userLabel = new JLabel("Username:");
        userLabel.setBounds(10, 20, 80, 25);
        panel.add(userLabel);

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
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                SimpleLoginPage loginPage = new SimpleLoginPage();
                loginPage.setVisible(true);
            }
        });
    }
}