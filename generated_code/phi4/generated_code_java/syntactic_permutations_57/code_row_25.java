import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {

    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    
    // Dummy data for demonstration purposes
    private String loggedInUserEmail = "user@example.com";
    private String userPassword = "password123";

    public SimpleLoginPage() {
        setTitle("Change Email");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        placeComponents(panel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                char[] confirmPass = confirmPasswordField.getPassword();
                String newEmail = newEmailField.getText();

                if (loggedInUserEmail.equals(oldEmail)) {
                    if (String.valueOf(confirmPass).equals(userPassword)) {
                        JOptionPane.showMessageDialog(null, "Email changed successfully to: " + newEmail);
                        loggedInUserEmail = newEmail;
                        // Clear fields
                        oldEmailField.setText("");
                        confirmPasswordField.setText("");
                        newEmailField.setText("");
                    } else {
                        JOptionPane.showMessageDialog(null, "Incorrect password.");
                    }
                } else {
                    JOptionPane.showMessageDialog(null, "Old email does not match the logged-in user's email.");
                }

                // Clear confirm password field for security
                java.util.Arrays.fill(confirmPass, ' ');
            }
        });
    }

    private void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailLabel.setBounds(10, 10, 80, 25);
        panel.add(oldEmailLabel);

        oldEmailField = new JTextField(20);
        oldEmailField.setBounds(100, 10, 160, 25);
        panel.add(oldEmailField);

        JLabel newPasswordLabel = new JLabel("Confirm Password:");
        newPasswordLabel.setBounds(10, 40, 120, 25);
        panel.add(newPasswordLabel);

        confirmPasswordField = new JPasswordField(20);
        confirmPasswordField.setBounds(130, 40, 140, 25);
        panel.add(confirmPasswordField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailLabel.setBounds(10, 70, 80, 25);
        panel.add(newEmailLabel);

        newEmailField = new JTextField(20);
        newEmailField.setBounds(100, 70, 160, 25);
        panel.add(newEmailField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.setBounds(10, 100, 250, 25);
        panel.add(changeEmailButton);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            SimpleLoginPage loginPage = new SimpleLoginPage();
            loginPage.setVisible(true);
        });
    }
}