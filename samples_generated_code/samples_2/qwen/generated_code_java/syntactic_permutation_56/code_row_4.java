import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField, confirmPasswordField;
    private JPasswordField passwordField;
    private JButton submitButton;
    private String correctPassword = "password123"; // Example password for demonstration

    public LoginPage() {
        setTitle("Update Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        getContentPane().add(panel);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        panel.add(oldEmailLabel);

        oldEmailField = new JTextField(20);
        panel.add(oldEmailField);

        JLabel passwordLabel = new JLabel("Password:");
        panel.add(passwordLabel);

        passwordField = new JPasswordField(20);
        panel.add(passwordField);

        JLabel newEmailLabel = new JLabel("New Email:");
        panel.add(newEmailLabel);

        newEmailField = new JTextField(20);
        panel.add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        panel.add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField(20);
        panel.add(confirmPasswordField);

        submitButton = new JButton("Submit");
        panel.add(submitButton);
        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String password = new String(passwordField.getPassword());
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (!password.equals(correctPassword)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password!", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (oldEmail.isEmpty() || newEmail.isEmpty() || confirmPassword.isEmpty()) {
                    JOptionPane.showMessageDialog(LoginPage.this, "All fields must be filled!", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!newEmail.equals(confirmPassword)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "New email and confirm password do not match!", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (oldEmail.equals(newEmail)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "New email must be different from old email!", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    JOptionPane.showMessageDialog(LoginPage.this, "Email updated successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                    // Here you would typically update the user's email in your database
                }
            }
        });
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