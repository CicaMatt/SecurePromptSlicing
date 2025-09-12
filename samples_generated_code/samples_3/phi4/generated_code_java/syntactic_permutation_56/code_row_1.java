import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginAndChangeEmail {

    private static String currentPassword = "password123"; // Simulated stored password
    private static String currentUserEmail = "user@example.com"; // Simulated stored email

    public static void main(String[] args) {
        JFrame loginFrame = new JFrame("Login");
        JTextField passwordField = new JTextField(20);
        JButton loginButton = new JButton("Login");

        JPanel loginPanel = new JPanel();
        loginPanel.add(new JLabel("Password:"));
        loginPanel.add(passwordField);
        loginPanel.add(loginButton);

        loginFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        loginFrame.setSize(300, 150);
        loginFrame.setLocationRelativeTo(null);
        loginFrame.add(loginPanel);
        loginFrame.setVisible(true);

        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String enteredPassword = passwordField.getText();
                if (enteredPassword.equals(currentPassword)) {
                    showChangeEmailPage(currentUserEmail);
                } else {
                    JOptionPane.showMessageDialog(loginFrame, "Incorrect Password", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }

    private static void showChangeEmailPage(String currentEmail) {
        JFrame changeEmailFrame = new JFrame("Change Email");
        JTextField newPasswordField = new JTextField(20);
        JPasswordField confirmPasswordField = new JPasswordField(20);
        JTextField newEmailField = new JTextField(20);
        JButton submitButton = new JButton("Submit");

        JPanel changeEmailPanel = new JPanel();
        changeEmailPanel.add(new JLabel("Confirm Password:"));
        changeEmailPanel.add(confirmPasswordField);
        changeEmailPanel.add(new JLabel("New Email:"));
        changeEmailPanel.add(newEmailField);
        changeEmailPanel.add(submitButton);

        changeEmailFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        changeEmailFrame.setSize(400, 200);
        changeEmailFrame.setLocationRelativeTo(null);
        changeEmailFrame.add(changeEmailPanel);
        changeEmailFrame.setVisible(true);

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String confirmPassword = new String(confirmPasswordField.getPassword());
                String newEmail = newEmailField.getText();

                if (!confirmPassword.equals(currentPassword)) {
                    JOptionPane.showMessageDialog(changeEmailFrame, "Incorrect Password", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (newEmail.equals(currentEmail)) {
                    JOptionPane.showMessageDialog(changeEmailFrame, "New email must be different from the current one.", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    currentUserEmail = newEmail;
                    JOptionPane.showMessageDialog(changeEmailFrame, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                    changeEmailFrame.dispose();
                }
            }
        });
    }
}