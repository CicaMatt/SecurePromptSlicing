import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginFrame extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JLabel statusLabel;

    public LoginFrame() {
        setTitle("Login Page");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        UsernameLabel userLabel = new UsernameLabel();
        panel.add(userLabel);

        usernameField = new JTextField(15);
        panel.add(usernameField);

        PasswordLabel passwordLabel = new PasswordLabel();
        panel.add(passwordLabel);

        passwordField = new JPasswordField(15);
        panel.add(passwordField);

        LoginButton loginButton = new LoginButton(panel, this);
        panel.add(loginButton);

        statusLabel = new JLabel("", SwingConstants.CENTER);
        panel.add(statusLabel);

        setVisible(true);
    }

    public boolean checkCredentials(String username, String password) {
        return "admin".equals(username) && "password123".equals(password);
    }

    private void redirectToSessionPage() {
        JOptionPane.showMessageDialog(this,
                "Login Successful! Redirecting to session page...",
                "Success",
                JOptionPane.INFORMATION_MESSAGE);
        // Here you might redirect or open a new frame for the session
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(LoginFrame::new);
    }

    private class LoginButton extends JButton implements ActionListener {
        JPanel panel;
        LoginFrame loginFrame;

        public LoginButton(JPanel panel, LoginFrame loginFrame) {
            super("Login");
            this.panel = panel;
            this.loginFrame = loginFrame;
            addActionListener(this);
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            String username = usernameField.getText();
            String password = new String(passwordField.getPassword());

            if (loginFrame.checkCredentials(username, password)) {
                redirectToSessionPage();
            } else {
                statusLabel.setText("Incorrect username or password");
            }
        }
    }

    private class UsernameLabel extends JLabel {
        public UsernameLabel() {
            setText("Username:");
        }
    }

    private class PasswordLabel extends JLabel {
        public PasswordLabel() {
            setText("Password:");
        }
    }
}