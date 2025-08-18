import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField emailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private String existingEmail = "user@example.com"; // Example existing email
    private String password = "password123"; // Example password

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(4, 2));

        JLabel emailLabel = new JLabel("Existing Email:");
        emailField = new JTextField(15);
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField(15);
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField(15);
        changeEmailButton = new JButton("Change Email");

        panel.add(emailLabel);
        panel.add(emailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String email = emailField.getText();
                String newEmail = newEmailField.getText();
                char[] passwordArray = confirmPasswordField.getPassword();
                String confirmPassword = new String(passwordArray);

                if (existingEmail.equals(email) && password.equals(confirmPassword)) {
                    existingEmail = newEmail;
                    JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully!");
                } else {
                    JOptionPane.showMessageDialog(LoginPage.this, "Incorrect email or password!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginPage().setVisible(true);
            }
        });
    }
}