import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private String currentUser = "example@example.com"; // Simulated logged in user
    private String currentPassword = "password123"; // Simulated password for the logged-in user

    public LoginPage() {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        add(oldEmailLabel);
        oldEmailField = new JTextField();
        add(oldEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        add(newEmailLabel);
        newEmailField = new JTextField();
        add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        add(confirmPasswordLabel);
        confirmPasswordField = new JPasswordField();
        add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        add(changeEmailButton);
        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (oldEmail.equals(currentUser)) {
                    if (confirmPassword.equals(currentPassword)) {
                        currentUser = newEmail;
                        JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully!");
                    } else {
                        JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password. Please try again.");
                    }
                } else {
                    JOptionPane.showMessageDialog(LoginPage.this, "Old email does not match the current user's email.");
                }

                oldEmailField.setText("");
                newEmailField.setText("");
                confirmPasswordField.setText("");
            }
        });

        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginPage();
            }
        });
    }
}