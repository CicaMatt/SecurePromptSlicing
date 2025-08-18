import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLogin extends JFrame {

    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public SimpleLogin() {
        setTitle("Simple Login");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        JLabel userLabel = new JLabel("Username:");
        panel.add(userLabel);

        usernameField = new JTextField(15);
        panel.add(usernameField);

        JLabel passwordLabel = new JLabel("Password:");
        panel.add(passwordLabel);

        passwordField = new JPasswordField(15);
        panel.add(passwordField);

        loginButton = new JButton("Login");
        panel.add(loginButton);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] password = passwordField.getPassword();

                if (username.equals("user") && new String(password).equals("pass")) {
                    JOptionPane.showMessageDialog(SimpleLogin.this, "Login successful!");
                    openSessionPage();
                } else {
                    JOptionPane.showMessageDialog(SimpleLogin.this, "Incorrect username or password.");
                }
            }
        });
    }

    private void openSessionPage() {
        JFrame sessionFrame = new JFrame("Session");
        sessionFrame.setSize(300, 100);
        JLabel messageLabel = new JLabel("Welcome to the session page!");
        sessionFrame.add(messageLabel);

        JButton logoutButton = new JButton("Logout");
        sessionFrame.add(logoutButton, "South");

        logoutButton.addActionListener(e -> {
            sessionFrame.dispose();
            this.setVisible(true);
        });

        sessionFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        sessionFrame.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new SimpleLogin().setVisible(true));
    }
}