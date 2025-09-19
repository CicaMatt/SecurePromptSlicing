import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginApp {
    private JFrame frame;
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            try {
                LoginApp window = new LoginApp();
                window.frame.setVisible(true);
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }

    public LoginApp() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame();
        frame.setBounds(100, 100, 350, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel usernameLabel = new JLabel("Username:");
        usernameLabel.setBounds(20, 20, 86, 14);
        frame.getContentPane().add(usernameLabel);

        usernameField = new JTextField();
        usernameField.setBounds(115, 17, 193, 20);
        frame.getContentPane().add(usernameField);
        usernameField.setColumns(10);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(20, 50, 86, 14);
        frame.getContentPane().add(passwordLabel);

        passwordField = new JPasswordField();
        passwordField.setBounds(115, 47, 193, 20);
        frame.getContentPane().add(passwordField);

        loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onButtonClick();
            }
        });
        loginButton.setBounds(115, 80, 86, 23);
        frame.getContentPane().add(loginButton);
    }

    private void onButtonClick() {
        String username = usernameField.getText();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars);

        if (check_mod(username, password)) {
            JOptionPane.showMessageDialog(frame, "Login Successful!");
        } else {
            JOptionPane.showMessageDialog(frame, "Invalid Username or Password.");
        }
    }

    private boolean check_mod(String username, String password) {
        return "admin".equals(username) && "password123".equals(password);
    }
}