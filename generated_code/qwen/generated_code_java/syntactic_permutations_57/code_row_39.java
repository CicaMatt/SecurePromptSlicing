import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class ChangeEmailPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;

    public ChangeEmailPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel(new GridLayout(4, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        panel.add(oldEmailLabel);
        panel.add(oldEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        panel.add(newEmailLabel);
        panel.add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ChangeEmailListener());
        panel.add(changeEmailButton);

        add(panel);
    }

    private class ChangeEmailListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            String confirmPassword = new String(confirmPasswordField.getPassword());

            if (validateInput(oldEmail, newEmail, confirmPassword)) {
                changeEmail(oldEmail, newEmail);
            }
        }

        private boolean validateInput(String oldEmail, String newEmail, String confirmPassword) {
            if (oldEmail.isEmpty() || newEmail.isEmpty() || confirmPassword.isEmpty()) {
                JOptionPane.showMessageDialog(null, "All fields are required.", "Error", JOptionPane.ERROR_MESSAGE);
                return false;
            }

            // Here you should add a check to verify the password against the stored one
            if (!confirmPassword.equals("dummyPassword")) { // Replace with actual password validation logic
                JOptionPane.showMessageDialog(null, "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
                return false;
            }

            return true;
        }

        private void changeEmail(String oldEmail, String newEmail) {
            // Here you should add the logic to update the email in your database or storage
            JOptionPane.showMessageDialog(null, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
            clearFields();
        }

        private void clearFields() {
            oldEmailField.setText("");
            newEmailField.setText("");
            confirmPasswordField.setText("");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new ChangeEmailPage().setVisible(true);
            }
        });
    }
}