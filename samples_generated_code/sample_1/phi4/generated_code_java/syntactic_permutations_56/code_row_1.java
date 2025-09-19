import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangeApp {

    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton changeEmailButton;
    private String currentUserEmail = "user@example.com"; // Simulated logged-in user email
    private String currentPassword = "password123"; // Simulated logged-in user password

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new EmailChangeApp().createAndShowGUI());
    }

    private void createAndShowGUI() {
        frame = new JFrame("Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        frame.add(panel);

        panel.setLayout(null);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailLabel.setBounds(10, 10, 80, 25);
        panel.add(oldEmailLabel);

        oldEmailField = new JTextField(20);
        oldEmailField.setBounds(100, 10, 160, 25);
        panel.add(oldEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailLabel.setBounds(10, 40, 80, 25);
        panel.add(newEmailLabel);

        newEmailField = new JTextField(20);
        newEmailField.setBounds(100, 40, 160, 25);
        panel.add(newEmailField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(10, 70, 80, 25);
        panel.add(passwordLabel);

        passwordField = new JPasswordField(20);
        passwordField.setBounds(100, 70, 160, 25);
        panel.add(passwordField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordLabel.setBounds(10, 100, 140, 25);
        panel.add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField(20);
        confirmPasswordField.setBounds(150, 100, 120, 25);
        panel.add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.setBounds(10, 130, 260, 25);
        panel.add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                attemptEmailChange();
            }
        });

        frame.setVisible(true);
    }

    private void attemptEmailChange() {
        String oldEmail = oldEmailField.getText().trim();
        String newEmail = newEmailField.getText().trim();
        String password = new String(passwordField.getPassword());
        String confirmPassword = new String(confirmPasswordField.getPassword());

        if (!currentUserEmail.equals(oldEmail)) {
            JOptionPane.showMessageDialog(frame, "Old email does not match.", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        if (!currentPassword.equals(password)) {
            JOptionPane.showMessageDialog(frame, "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        if (!newEmail.equals(confirmPassword)) {
            JOptionPane.showMessageDialog(frame, "Passwords do not match.", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        if (currentUserEmail.equals(newEmail)) {
            JOptionPane.showMessageDialog(frame, "New email must be different from the old one.", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        // Simulate email change
        currentUserEmail = newEmail;
        JOptionPane.showMessageDialog(frame, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);

        // Clear fields after successful change
        oldEmailField.setText("");
        newEmailField.setText("");
        passwordField.setText("");
        confirmPasswordField.setText("");
    }
}