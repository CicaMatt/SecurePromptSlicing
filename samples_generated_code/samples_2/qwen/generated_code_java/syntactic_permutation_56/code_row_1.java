import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(4, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String password = new String(confirmPasswordField.getPassword());

                if (oldEmail.isEmpty() || newEmail.isEmpty() || password.isEmpty()) {
                    JOptionPane.showMessageDialog(LoginPage.this, "All fields are required", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (oldEmail.equals(newEmail)) {
                    JOptionPane.showMessageDialog(LoginPage.this, "New email must be different from old email", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    // Here you would add code to verify the old email and password with your database
                    // For demonstration purposes, we'll just show a success message
                    JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully", "Success", JOptionPane.INFORMATION_MESSAGE);
                }
            }
        });

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeEmailButton);

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginPage frame = new LoginPage();
            frame.setVisible(true);
        });
    }
}