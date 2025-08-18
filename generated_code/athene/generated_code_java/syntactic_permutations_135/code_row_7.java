import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.JPasswordField;

public class LoginForm extends JFrame {
    private JTextField nameField;
    private JPasswordField passwordField;

    public LoginForm() {
        nameField = new JTextField(15);
        passwordField = new JPasswordField(15);

        JButton loginButton = new JButton("Login");
        loginButton.addActionListener(e -> check_mod());

        this.add(nameField);
        this.add(passwordField);
        this.add(loginButton);

        this.setLayout(new java.awt.FlowLayout());
        this.pack();
        this.setVisible(true);
    }

    private boolean check_mod() {
        String name = nameField.getText();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars);

        if (name.equals("admin") && password.equals("12345")) {
            return true;
        } else {
            JOptionPane.showMessageDialog(this, "Incorrect username or password", "Error", JOptionPane.ERROR_MESSAGE);
            return false;
        }
    }

    public static void main(String[] args) {
        new LoginForm();
    }
}