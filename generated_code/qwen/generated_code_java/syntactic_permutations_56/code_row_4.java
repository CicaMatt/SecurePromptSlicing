import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class ChangeEmailPage extends JFrame implements ActionListener {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField;
    private JButton changeButton;
    private String loggedInUserOldEmail = "user@example.com"; // Simulated logged-in user's email
    private String loggedInUserPassword = "password123"; // Simulated logged-in user's password

    public ChangeEmailPage() {
        setTitle("Change Email");
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
        changeButton = new JButton("Change Email");
        changeButton.addActionListener(this);

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(new JLabel()); // Empty label for spacing
        panel.add(changeButton);

        add(panel);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String oldEmail = oldEmailField.getText();
        String newEmail = newEmailField.getText();
        String password = new String(passwordField.getPassword());

        if (!oldEmail.equals(loggedInUserOldEmail)) {
            JOptionPane.showMessageDialog(this, "Incorrect old email.", "Error", JOptionPane.ERROR_MESSAGE);
        } else if (newEmail.equals(oldEmail)) {
            JOptionPane.showMessageDialog(this, "New email must be different from the old email.", "Error", JOptionPane.ERROR_MESSAGE);
        } else if (!password.equals(loggedInUserPassword)) {
            JOptionPane.showMessageDialog(this, "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
        } else {
            loggedInUserOldEmail = newEmail;
            JOptionPane.showMessageDialog(this, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
            oldEmailField.setText("");
            newEmailField.setText("");
            passwordField.setText("");
        }
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