import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginForm extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton submitButton;

    public LoginForm() {
        usernameField = new JTextField(20);
        passwordField = new JPasswordField(20);
        submitButton = new JButton("Login");

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean isMod = check_mod();
                if (isMod) {
                    JOptionPane.showMessageDialog(LoginForm.this, "Login successful!");
                } else {
                    JOptionPane.showMessageDialog(LoginForm.this, "Invalid username or password", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        this.setLayout(new BoxLayout(this.getContentPane(), BoxLayout.Y_AXIS));
        this.add(usernameField);
        this.add(passwordField);
        this.add(submitButton);

        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.pack();
        this.setVisible(true);
    }

    private boolean check_mod() {
        String username = usernameField.getText();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars);

        // Example correct credentials
        if ("admin".equals(username) && "password123".equals(password)) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        new LoginForm();
    }
}