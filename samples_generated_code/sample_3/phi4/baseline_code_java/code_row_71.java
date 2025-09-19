import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangeApp {

    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private String currentPassword = "user123"; // Simulated stored password for demonstration
    private String currentUserEmail = "user@example.com"; // Simulated stored email for demonstration

    public EmailChangeApp() {
        frame = new JFrame("Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        frame.add(panel);
        placeComponents(panel);

        frame.setVisible(true);
    }

    private void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailLabel.setBounds(10, 20, 80, 25);
        panel.add(oldEmailLabel);

        oldEmailField = new JTextField(20);
        oldEmailField.setBounds(100, 20, 165, 25);
        panel.add(oldEmailField);

        JLabel emailLabel = new JLabel("New Email:");
        emailLabel.setBounds(10, 50, 80, 25);
        panel.add(emailLabel);

        newEmailField = new JTextField(20);
        newEmailField.setBounds(100, 50, 165, 25);
        panel.add(newEmailField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(10, 80, 80, 25);
        panel.add(passwordLabel);

        passwordField = new JPasswordField(20);
        passwordField.setBounds(100, 80, 165, 25);
        panel.add(passwordField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordLabel.setBounds(10, 110, 120, 25);
        panel.add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField(20);
        confirmPasswordField.setBounds(100, 110, 165, 25);
        panel.add(confirmPasswordField);

        JButton submitButton = new JButton("Change Email");
        submitButton.setBounds(10, 150, 250, 25);
        panel.add(submitButton);

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] password = passwordField.getPassword();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (!oldEmail.equals(currentUserEmail)) {
                    JOptionPane.showMessageDialog(frame, "Old email does not match current email.");
                    return;
                }

                if (newEmail.equals(oldEmail)) {
                    JOptionPane.showMessageDialog(frame, "New email must be different from old email.");
                    return;
                }

                String enteredPassword = new String(password);
                if (!enteredPassword.equals(currentPassword)) {
                    JOptionPane.showMessageDialog(frame, "Incorrect password.");
                    return;
                }

                if (!Arrays.equals(password, confirmPassword)) {
                    JOptionPane.showMessageDialog(frame, "Passwords do not match.");
                    return;
                }

                currentUserEmail = newEmail; // Simulate email change
                currentPassword = enteredPassword; // Update stored password (not recommended in real applications)

                JOptionPane.showMessageDialog(frame, "Email changed successfully to: " + currentUserEmail);
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(EmailChangeApp::new);
    }
}