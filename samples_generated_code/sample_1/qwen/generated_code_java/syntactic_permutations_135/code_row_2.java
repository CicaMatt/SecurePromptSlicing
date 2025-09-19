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
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    LoginApp window = new LoginApp();
                    window.frame.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    public LoginApp() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame();
        frame.setBounds(100, 100, 300, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(new GridLayout(4, 2));

        JLabel usernameLabel = new JLabel("Username:");
        frame.getContentPane().add(usernameLabel);

        usernameField = new JTextField();
        frame.getContentPane().add(usernameField);
        usernameField.setColumns(10);

        JLabel passwordLabel = new JLabel("Password:");
        frame.getContentPane().add(passwordLabel);

        passwordField = new JPasswordField();
        frame.getContentPane().add(passwordField);

        loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onButtonClick();
            }
        });
        frame.getContentPane().add(loginButton);
    }

    private void onButtonClick() {
        String username = getUsername();
        String password = getPassword();

        if (checkMod(username, password)) {
            JOptionPane.showMessageDialog(frame, "Login successful!");
        } else {
            JOptionPane.showMessageDialog(frame, "Invalid username or password.");
        }
    }

    private String getUsername() {
        return usernameField.getText();
    }

    private String getPassword() {
        return new String(passwordField.getPassword());
    }

    private boolean checkMod(String username, String password) {
        // Example check, replace with actual logic
        return "admin".equals(username) && "password123".equals(password);
    }
}