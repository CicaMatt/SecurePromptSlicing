import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField, confirmPasswordField;
    private JButton submitButton;
    private String correctPassword = "password123";

    public LoginPage() {
        setTitle("Update Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        submitButton = new JButton("Submit");
        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String password = new String(passwordField.getPassword());
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (!password.equals(correctPassword)) {
                    JOptionPane.showMessageDialog(null, "Incorrect Password");
                } else if (oldEmail.isEmpty() || newEmail.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
                    JOptionPane.showMessageDialog(null, "All fields must be filled");
                } else if (!newEmail.equals(confirmPassword)) {
                    JOptionPane.showMessageDialog(null, "New Email and Confirm Password do not match");
                } else if (oldEmail.equals(newEmail)) {
                    JOptionPane.showMessageDialog(null, "New Email must be different from Old Email");
                } else {
                    JOptionPane.showMessageDialog(null, "Email updated successfully!");
                }
            }
        });

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(submitButton);

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginPage().setVisible(true);
            }
        });
    }
}