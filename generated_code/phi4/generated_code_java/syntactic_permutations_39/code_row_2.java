import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLogin extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;
    private JLabel messageLabel;

    public SimpleLogin() {
        setTitle("Simple Login");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        UsernameLabel userLabel = new UsernameLabel();
        panel.add(userLabel);
        usernameField = new JTextField(20);
        panel.add(usernameField);

        PasswordLabel passwordLabel = new PasswordLabel();
        panel.add(passwordLabel);
        passwordField = new JPasswordField(20);
        panel.add(passwordField);

        loginButton = new JButton("Login");
        panel.add(loginButton);

        messageLabel = new JLabel("", SwingConstants.CENTER);
        panel.add(messageLabel);

        ActionListener actionListener = new LoginActionListener();
        loginButton.addActionListener(actionListener);
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

    private class LoginActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String username = usernameField.getText();
            String password = new String(passwordField.getPassword());

            if (username.equals("user") && password.equals("pass")) { // Replace with actual validation logic
                JOptionPane.showMessageDialog(SimpleLogin.this, "Login successful!", "Success", JOptionPane.INFORMATION_MESSAGE);
                // Redirect to session page or another action
            } else {
                messageLabel.setText("Incorrect username or password");
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            SimpleLogin frame = new SimpleLogin();
            frame.setVisible(true);
        });
    }
}