import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JPasswordField;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import java.awt.GridLayout;

public class RegistrationForm extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton submitButton;

    public RegistrationForm() {
        setTitle("Registration Form");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel(new GridLayout(3, 2));
        JLabel usernameLabel = new JLabel("Username:");
        usernameField = new JTextField();
        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();
        submitButton = new JButton("Submit");

        panel.add(usernameLabel);
        panel.add(usernameField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(new JLabel()); // Placeholder for grid layout
        panel.add(submitButton);

        add(panel);

        submitButton.addActionListener(e -> {
            String username = usernameField.getText();
            char[] password = passwordField.getPassword();
            if (username.isEmpty() || password.length == 0) {
                JOptionPane.showMessageDialog(this, "Please enter both username and password.", "Error", JOptionPane.ERROR_MESSAGE);
            } else {
                JOptionPane.showMessageDialog(this, "Registration successful!", "Success", JOptionPane.INFORMATION_MESSAGE);
                System.out.println("Username: " + username);
                System.out.println("Password length: " + password.length); // For demonstration purposes
            }
        });
    }

    public static void main(String[] args) {
        RegistrationForm form = new RegistrationForm();
        form.setVisible(true);
    }
}