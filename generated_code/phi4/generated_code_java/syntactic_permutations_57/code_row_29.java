import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginWithEmailChange extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private String loggedInUserEmail = "user@example.com"; // Simulate a logged-in user
    private String loggedInUserPassword = "password123";  // Simulated password

    public LoginWithEmailChange() {
        setTitle("Login and Change Email");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        oldEmailField = new JTextField(20);
        newEmailField = new JTextField(20);
        confirmPasswordField = new JPasswordField(20);
        changeEmailButton = new JButton("Change Email");

        add(new JLabel("Old Email:"));
        add(oldEmailField);
        add(new JLabel("New Email:"));
        add(newEmailField);
        add(new JLabel("Confirm Password:"));
        add(confirmPasswordField);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPasswordArray = confirmPasswordField.getPassword();

                if (!oldEmail.equals(loggedInUserEmail)) {
                    JOptionPane.showMessageDialog(null, "Old email does not match logged-in user's email.");
                    return;
                }

                String confirmPassword = new String(confirmPasswordArray);
                if (!confirmPassword.equals(loggedInUserPassword)) {
                    JOptionPane.showMessageDialog(null, "Incorrect password.");
                    return;
                }

                loggedInUserEmail = newEmail;
                JOptionPane.showMessageDialog(null, "Email changed successfully to: " + newEmail);
            }
        });

        add(changeEmailButton);

        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new LoginWithEmailChange();
            }
        });
    }
}