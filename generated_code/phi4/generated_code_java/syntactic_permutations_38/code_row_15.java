import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public SimpleLoginPage() {
        setTitle("Simple Login Page");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

        usernameField = new JTextField();
        passwordField = new JPasswordField();

        loginButton = new JButton("Login");

        panel.add(new JLabel("Username:"));
        panel.add(usernameField);
        panel.add(new JLabel("Password:"));
        panel.add(passwordField);
        panel.add(loginButton);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                if (authenticate(username, password)) {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Login Successful!",
                            "Success",
                            JOptionPane.INFORMATION_MESSAGE);
                    redirectToDashboard();
                } else {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Invalid username or password.",
                            "Error",
                            JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }

    private boolean authenticate(String username, String password) {
        // Simple authentication logic (username: user, password: pass)
        return "user".equals(username) && "pass".equals(password);
    }

    private void redirectToDashboard() {
        // Logic to redirect to dashboard
        JOptionPane.showMessageDialog(this,
                "Redirecting to Dashboard...",
                "Info",
                JOptionPane.INFORMATION_MESSAGE);

        // In a real application, you might open a new frame here.
        // For demonstration purposes, we just close the login window.
        this.dispose();
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