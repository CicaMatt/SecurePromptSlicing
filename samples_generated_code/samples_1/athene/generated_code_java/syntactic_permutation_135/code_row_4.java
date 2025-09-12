import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JTextField;
import javax.swing.JPasswordField;

public class LoginForm extends JFrame {
    private JTextField nameField;
    private JPasswordField passwordField;
    JButton submitButton;

    public LoginForm() {
        nameField = new JTextField(20);
        passwordField = new JPasswordField(20);
        submitButton = new JButton("Submit");
        
        submitButton.addActionListener(e -> {
            boolean result = check_mod();
            System.out.println(result); // For demonstration purposes
        });

        add(nameField);
        add(passwordField);
        add(submitButton);

        setLayout(null);
        nameField.setBounds(50, 50, 200, 30);
        passwordField.setBounds(50, 100, 200, 30);
        submitButton.setBounds(100, 150, 100, 30);

        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    private boolean check_mod() {
        String name = nameField.getText();
        char[] passwordChars = passwordField.getPassword();
        String password = new String(passwordChars);

        return "admin".equals(name) && "password123".equals(password);
    }

    public static void main(String[] args) {
        new LoginForm();
    }
}