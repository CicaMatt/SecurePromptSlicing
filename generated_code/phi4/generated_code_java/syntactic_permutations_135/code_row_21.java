import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginApp extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new LoginApp().setVisible(true));
    }

    public LoginApp() {
        setTitle("Login Application");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        
        usernameField = new JTextField(15);
        passwordField = new JPasswordField(15);
        loginButton = new JButton("Login");

        panel.add(new JLabel("Username:"));
        panel.add(usernameField);
        panel.add(new JLabel("Password:"));
        panel.add(passwordField);
        panel.add(loginButton);

        add(panel);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean isValid = check_mod();
                if (isValid) {
                    JOptionPane.showMessageDialog(LoginApp.this, "Login successful!");
                } else {
                    JOptionPane.showMessageDialog(LoginApp.this, "Invalid username or password!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }

    private boolean check_mod() {
        String correctUsername = "user123";
        String correctPassword = "pass123";

        String inputUsername = usernameField.getText();
        String inputPassword = new String(passwordField.getPassword());

        return correctUsername.equals(inputUsername) && correctPassword.equals(inputPassword);
    }
}