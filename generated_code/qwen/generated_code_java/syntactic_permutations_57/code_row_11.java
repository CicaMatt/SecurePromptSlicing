import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangeApp {
    private JFrame frame;
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private JLabel messageLabel;

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            try {
                EmailChangeApp window = new EmailChangeApp();
                window.frame.setVisible(true);
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }

    public EmailChangeApp() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame();
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel lblOldEmail = new JLabel("Old Email:");
        lblOldEmail.setBounds(60, 27, 89, 14);
        frame.getContentPane().add(lblOldEmail);

        oldEmailField = new JTextField();
        oldEmailField.setBounds(159, 24, 200, 20);
        frame.getContentPane().add(oldEmailField);
        oldEmailField.setColumns(10);

        JLabel lblNewEmail = new JLabel("New Email:");
        lblNewEmail.setBounds(60, 67, 89, 14);
        frame.getContentPane().add(lblNewEmail);

        newEmailField = new JTextField();
        newEmailField.setBounds(159, 64, 200, 20);
        frame.getContentPane().add(newEmailField);
        newEmailField.setColumns(10);

        JLabel lblConfirmPassword = new JLabel("Confirm Password:");
        lblConfirmPassword.setBounds(27, 108, 122, 14);
        frame.getContentPane().add(lblConfirmPassword);

        confirmPasswordField = new JPasswordField();
        confirmPasswordField.setBounds(159, 105, 200, 20);
        frame.getContentPane().add(confirmPasswordField);

        changeButton = new JButton("Change Email");
        changeButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] passwordChars = confirmPasswordField.getPassword();
                String confirmPassword = new String(passwordChars);

                if (validateInputs(oldEmail, newEmail, confirmPassword)) {
                    changeEmail(oldEmail, newEmail);
                    messageLabel.setText("Email changed successfully!");
                } else {
                    messageLabel.setText("Invalid input or incorrect confirmation.");
                }
            }
        });
        changeButton.setBounds(169, 148, 120, 23);
        frame.getContentPane().add(changeButton);

        messageLabel = new JLabel("");
        messageLabel.setForeground(Color.RED);
        messageLabel.setBounds(75, 180, 300, 14);
        frame.getContentPane().add(messageLabel);
    }

    private boolean validateInputs(String oldEmail, String newEmail, String confirmPassword) {
        // In a real application, you would check if the old email exists and
        // if the confirm password matches the stored password for that email.
        // Here, we assume the old email is "test@example.com" and the password is "password".
        return "test@example.com".equals(oldEmail) && "password".equals(confirmPassword) && !newEmail.isEmpty();
    }

    private void changeEmail(String oldEmail, String newEmail) {
        // Logic to change email in a database or storage system.
        System.out.println("Changing email from " + oldEmail + " to " + newEmail);
    }
}