import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField oldEmailField;
    private JPasswordField confirmPasswordField;
    private JTextField newEmailField;
    private JLabel statusLabel;
    private JButton changeEmailButton;

    private String userEmail = "user@example.com"; // Simulated logged-in user email
    private String userPassword = "password123";  // Simulated correct password for the user

    public SimpleLoginPage() {
        setTitle("Change Email");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        oldEmailField = new JTextField();
        confirmPasswordField = new JPasswordField();
        newEmailField = new JTextField();

        JLabel oldEmailLabel = new JLabel("Old Email:");
        JLabel confirmPassLabel = new JLabel("Confirm Password:");
        JLabel newEmailLabel = new JLabel("New Email:");

        changeEmailButton = new JButton("Change Email");
        statusLabel = new JLabel("");

        add(oldEmailLabel);
        add(oldEmailField);
        add(confirmPassLabel);
        add(confirmPasswordField);
        add(newEmailLabel);
        add(newEmailField);
        add(changeEmailButton);
        add(statusLabel);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();
                String newEmail = newEmailField.getText();

                if (oldEmail.equals(userEmail)) {
                    if (new String(confirmPassword).equals(userPassword)) {
                        // Simulate email change
                        userEmail = newEmail;
                        JOptionPane.showMessageDialog(SimpleLoginPage.this,
                                "Email changed successfully to: " + newEmail);
                        statusLabel.setText("Email changed successfully.");
                    } else {
                        JOptionPane.showMessageDialog(SimpleLoginPage.this,
                                "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
                        statusLabel.setText("Incorrect password.");
                    }
                } else {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                            "Old email does not match current account email.", "Error", JOptionPane.ERROR_MESSAGE);
                    statusLabel.setText("Old email incorrect.");
                }
            }
        });

        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new SimpleLoginPage();
            }
        });
    }
}