import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChangeEmailPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    private String currentEmail = "user@example.com"; // Simulated logged-in user's email
    private char[] confirmPassword = {'p', 'a', 's', 's'}; // Simulated correct password

    public ChangeEmailPage() {
        setTitle("Change Email");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        setLayout(new GridLayout(4, 2));

        add(new JLabel("Old Email:"));
        oldEmailField = new JTextField();
        add(oldEmailField);

        add(new JLabel("New Email:"));
        newEmailField = new JTextField();
        add(newEmailField);

        add(new JLabel("Confirm Password:"));
        confirmPasswordField = new JPasswordField();
        add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    String oldEmail = oldEmailField.getText().trim();
                    String newEmail = newEmailField.getText().trim();
                    char[] inputPassword = confirmPasswordField.getPassword();

                    if (!oldEmail.equals(currentEmail)) {
                        JOptionPane.showMessageDialog(null, "Incorrect current email.");
                        return;
                    }

                    if (newEmail.isEmpty() || !newEmail.contains("@")) {
                        JOptionPane.showMessageDialog(null, "Please provide a valid new email.");
                        return;
                    }

                    if (inputPassword.length != confirmPassword.length) {
                        JOptionPane.showMessageDialog(null, "Confirm password is incorrect.");
                        return;
                    }

                    boolean passwordsMatch = true;
                    for (int i = 0; i < confirmPassword.length; i++) {
                        if (inputPassword[i] != confirmPassword[i]) {
                            passwordsMatch = false;
                            break;
                        }
                    }

                    if (!passwordsMatch) {
                        JOptionPane.showMessageDialog(null, "Confirm password is incorrect.");
                        return;
                    }

                    currentEmail = newEmail;
                    JOptionPane.showMessageDialog(null, "Email changed successfully!");

                } catch (Exception ex) {
                    JOptionPane.showMessageDialog(null, "An error occurred: " + ex.getMessage());
                }
            }
        });
        add(changeEmailButton);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new ChangeEmailPage().setVisible(true);
            }
        });
    }
}