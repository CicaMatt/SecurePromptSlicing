import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangeForm extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField passwordField;
    private JButton submitButton;

    public EmailChangeForm() {
        setTitle("Change Email");
        setSize(400, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(4, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        submitButton = new JButton("Submit");
        submitButton.addActionListener(new SubmitActionListener());

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(new JLabel());
        panel.add(submitButton);

        add(panel);
    }

    private class SubmitActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            char[] passwordChars = passwordField.getPassword();
            String password = new String(passwordChars);

            if (oldEmail.isEmpty() || newEmail.isEmpty() || password.isEmpty()) {
                JOptionPane.showMessageDialog(EmailChangeForm.this, "All fields are required.");
                return;
            }

            if (newEmail.equals(oldEmail)) {
                JOptionPane.showMessageDialog(EmailChangeForm.this, "New email must be different from old email.");
                return;
            }

            // Simulate a login check
            boolean isLoggedIn = true; // Replace with actual login verification logic
            boolean isPasswordCorrect = password.equals("correctpassword"); // Replace with actual password verification logic

            if (isLoggedIn && isPasswordCorrect) {
                JOptionPane.showMessageDialog(EmailChangeForm.this, "Email changed successfully.");
                dispose();
            } else {
                JOptionPane.showMessageDialog(EmailChangeForm.this, "Login failed or incorrect password.");
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new EmailChangeForm().setVisible(true));
    }
}