import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JPasswordField;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RegistrationForm extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;

    public RegistrationForm() {
        super("Registration Form");
        setLayout(new FlowLayout());

        JLabel usernameLabel = new JLabel("Username:");
        add(usernameLabel);
        usernameField = new JTextField(15);
        add(usernameField);

        JLabel passwordLabel = new JLabel("Password:");
        add(passwordLabel);
        passwordField = new JPasswordField(15);
        add(passwordField);

        JButton submitButton = new JButton("Register");
        add(submitButton);

        submitButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                char[] password = passwordField.getPassword();

                if (username.isEmpty() || password.length == 0) {
                    JOptionPane.showMessageDialog(RegistrationForm.this, "Please enter both username and password.", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    JOptionPane.showMessageDialog(RegistrationForm.this, "Registration successful!", "Success", JOptionPane.INFORMATION_MESSAGE);
                    // Clear fields after successful registration
                    usernameField.setText("");
                    passwordField.setText("");
                }
            }
        });

        pack();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public static void main(String[] args) {
        RegistrationForm form = new RegistrationForm();
        form.setVisible(true);
    }
}