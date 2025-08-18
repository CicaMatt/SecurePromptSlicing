import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangeForm extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton submitButton;
    private JLabel messageLabel;
    private String correctPassword = "correctpassword123";

    public EmailChangeForm() {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(5, 2));

        add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        add(oldEmailField);

        add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        add(newEmailField);

        add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        add(confirmPasswordField);

        submitButton = new JButton("Submit");
        add(submitButton);
        messageLabel = new JLabel("");
        add(messageLabel);

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText().trim();
                String newEmail = newEmailField.getText().trim();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (confirmPassword.equals(correctPassword)) {
                    if (!oldEmail.isEmpty() && !newEmail.isEmpty()) {
                        if (!oldEmail.equals(newEmail)) {
                            messageLabel.setText("Email changed successfully!");
                        } else {
                            messageLabel.setText("New email must be different from the old one.");
                        }
                    } else {
                        messageLabel.setText("Please enter both emails.");
                    }
                } else {
                    messageLabel.setText("Incorrect password.");
                }
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            EmailChangeForm form = new EmailChangeForm();
            form.setVisible(true);
        });
    }
}