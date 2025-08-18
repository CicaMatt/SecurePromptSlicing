import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private String loggedUserEmail = "user@example.com"; // Simulated logged-in user email
    private String loggedUserPassword = "password123"; // Simulated logged-in user password

    public LoginPage() {
        setTitle("Change Email");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel(new GridLayout(4, 2));
        JLabel oldEmailLabel = new JLabel("Old Email:");
        JLabel newEmailLabel = new JLabel("New Email:");
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");

        oldEmailField = new JTextField();
        newEmailField = new JTextField();
        confirmPasswordField = new JPasswordField();

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                String confirmPassword = new String(confirmPasswordField.getPassword());

                if (loggedUserEmail.equals(oldEmail)) {
                    if (loggedUserPassword.equals(confirmPassword)) {
                        loggedUserEmail = newEmail;
                        JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully!");
                    } else {
                        JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password. Please try again.", "Error", JOptionPane.ERROR_MESSAGE);
                    }
                } else {
                    JOptionPane.showMessageDialog(LoginPage.this, "Old email does not match the logged-in user's email.", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(new JLabel()); // Empty label for spacing
        panel.add(changeEmailButton);

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginPage loginPage = new LoginPage();
            loginPage.setVisible(true);
        });
    }
}