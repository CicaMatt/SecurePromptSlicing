import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage {
    private JFrame frame;
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private JLabel statusLabel;

    public LoginPage() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame("Login Page");
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailLabel.setBounds(60, 25, 80, 25);
        frame.getContentPane().add(oldEmailLabel);

        oldEmailField = new JTextField();
        oldEmailField.setBounds(150, 25, 200, 25);
        frame.getContentPane().add(oldEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailLabel.setBounds(60, 60, 80, 25);
        frame.getContentPane().add(newEmailLabel);

        newEmailField = new JTextField();
        newEmailField.setBounds(150, 60, 200, 25);
        frame.getContentPane().add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordLabel.setBounds(60, 95, 120, 25);
        frame.getContentPane().add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField();
        confirmPasswordField.setBounds(180, 95, 170, 25);
        frame.getContentPane().add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.setBounds(160, 140, 130, 25);
        frame.getContentPane().add(changeEmailButton);

        statusLabel = new JLabel("");
        statusLabel.setBounds(80, 175, 300, 25);
        frame.getContentPane().add(statusLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (validateInput(oldEmail, newEmail, confirmPassword)) {
                    changeEmail(oldEmail, newEmail);
                }
            }
        });
    }

    private boolean validateInput(String oldEmail, String newEmail, String confirmPassword) {
        if (!oldEmail.equals("user@example.com")) {
            statusLabel.setText("Old email does not exist.");
            return false;
        }
        if (confirmPassword.equals("password123")) {
            return true;
        } else {
            statusLabel.setText("Incorrect password.");
            return false;
        }
    }

    private void changeEmail(String oldEmail, String newEmail) {
        // Here you would implement the logic to change the email in your database
        statusLabel.setText("Email changed successfully from " + oldEmail + " to " + newEmail);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                try {
                    LoginPage window = new LoginPage();
                    window.frame.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }
}