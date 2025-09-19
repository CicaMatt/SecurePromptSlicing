import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(4, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        changeEmailButton = new JButton("Change Email");

        add(oldEmailLabel);
        add(oldEmailField);
        add(newEmailLabel);
        add(newEmailField);
        add(confirmPasswordLabel);
        add(confirmPasswordField);
        add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (isValidUser(oldEmail, confirmPassword)) {
                    changeEmail(oldEmail, newEmail);
                } else {
                    JOptionPane.showMessageDialog(LoginPage.this, "Invalid old email or password.", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        setVisible(true);
    }

    private boolean isValidUser(String email, String password) {
        // This method should check the database if the user exists with the provided email and password
        // For demonstration purposes, we assume that any non-empty email and password are valid
        return !email.isEmpty() && !password.isEmpty();
    }

    private void changeEmail(String oldEmail, String newEmail) {
        // This method should update the user's email in the database
        // For demonstration purposes, we just show a success message
        JOptionPane.showMessageDialog(this, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
    }

    public static void main(String[] args) {
        new LoginPage();
    }
}