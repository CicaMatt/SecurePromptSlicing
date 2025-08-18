import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangeForm extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private JLabel statusLabel;
    private String currentUserPassword;
    private String currentEmail;

    public EmailChangeForm(String email, String password) {
        this.currentEmail = email;
        this.currentUserPassword = password;
        setTitle("Change Email");
        setSize(400, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel(new GridLayout(0, 1));
        getContentPane().add(panel);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        changeButton = new JButton("Change Email");
        statusLabel = new JLabel("");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeButton);
        panel.add(statusLabel);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (oldEmail.equals(currentEmail)) {
                    if (!newEmail.equals(oldEmail)) {
                        if (String.valueOf(confirmPassword).equals(currentUserPassword)) {
                            currentEmail = newEmail;
                            statusLabel.setText("Email changed successfully.");
                        } else {
                            statusLabel.setText("Incorrect password.");
                        }
                    } else {
                        statusLabel.setText("New email must be different from the old one.");
                    }
                } else {
                    statusLabel.setText("Old email does not match the current email.");
                }
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            new EmailChangeForm("user@example.com", "password123").setVisible(true);
        });
    }
}