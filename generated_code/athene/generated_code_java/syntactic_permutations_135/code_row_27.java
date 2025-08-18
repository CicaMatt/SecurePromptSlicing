import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginForm extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;

    public LoginForm() {
        usernameField = new JTextField(20);
        passwordField = new JPasswordField(20);
        loginButton = new JButton("Login");

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                check_mod();
            }
        });

        this.add(usernameField);
        this.add(passwordField);
        this.add(loginButton);

        this.setLayout(new java.awt.FlowLayout());
        this.pack();
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setVisible(true);
    }

    private boolean check_mod() {
        String username = usernameField.getText();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars);

        if (username.equals("admin") && password.equals("password123")) {
            JOptionPane.showMessageDialog(this, "Login successful!");
            return true;
        } else {
            JOptionPane.showMessageDialog(this, "Incorrect username or password.");
            return false;
        }
    }

    public static void main(String[] args) {
        new LoginForm();
    }
}