import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage {
    private JFrame frame;
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField passwordField;
    private JPasswordField confirmPasswordField;
    private JButton loginButton;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginPage();
            }
        });
    }

    public LoginPage() {
        frame = new JFrame("Update Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);
        frame.setLayout(null);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailLabel.setBounds(50, 20, 100, 25);
        frame.add(oldEmailLabel);

        oldEmailField = new JTextField();
        oldEmailField.setBounds(160, 20, 200, 25);
        frame.add(oldEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailLabel.setBounds(50, 50, 100, 25);
        frame.add(newEmailLabel);

        newEmailField = new JTextField();
        newEmailField.setBounds(160, 50, 200, 25);
        frame.add(newEmailField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(50, 80, 100, 25);
        frame.add(passwordLabel);

        passwordField = new JPasswordField();
        passwordField.setBounds(160, 80, 200, 25);
        frame.add(passwordField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordLabel.setBounds(50, 110, 100, 25);
        frame.add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField();
        confirmPasswordField.setBounds(160, 110, 200, 25);
        frame.add(confirmPasswordField);

        loginButton = new JButton("Update");
        loginButton.setBounds(160, 150, 100, 25);
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] passwordChars = passwordField.getPassword();
                char[] confirmPasswordChars = confirmPasswordField.getPassword();

                if (!new String(passwordChars).equals("password")) {
                    JOptionPane.showMessageDialog(frame, "Incorrect Password", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (oldEmail.isEmpty() || newEmail.isEmpty() || passwordChars.length == 0 || confirmPasswordChars.length == 0) {
                    JOptionPane.showMessageDialog(frame, "All fields are required", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!new String(passwordChars).equals(new String(confirmPasswordChars))) {
                    JOptionPane.showMessageDialog(frame, "Passwords do not match", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (oldEmail.equals(newEmail)) {
                    JOptionPane.showMessageDialog(frame, "New email must be different from old email", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    JOptionPane.showMessageDialog(frame, "Email updated successfully", "Success", JOptionPane.INFORMATION_MESSAGE);
                }
            }
        });
        frame.add(loginButton);

        frame.setVisible(true);
    }
}