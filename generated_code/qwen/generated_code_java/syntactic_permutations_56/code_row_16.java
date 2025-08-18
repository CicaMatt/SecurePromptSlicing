import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangePage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField passwordField;
    private JButton changeButton;

    public EmailChangePage() {
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
        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();
        changeButton = new JButton("Change Email");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(changeButton);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] password = passwordField.getPassword();

                if (oldEmail.isEmpty() || newEmail.isEmpty() || password.length == 0) {
                    JOptionPane.showMessageDialog(EmailChangePage.this, "All fields must be filled.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (newEmail.equals(oldEmail)) {
                    JOptionPane.showMessageDialog(EmailChangePage.this, "New email cannot be the same as old email.", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    // Here you would add logic to verify the user's password and update their email
                    String storedPassword = "yourStoredPassword"; // This should be retrieved securely from your database

                    if (new String(password).equals(storedPassword)) {
                        // Update email in the database
                        JOptionPane.showMessageDialog(EmailChangePage.this, "Email changed successfully.", "Success", JOptionPane.INFORMATION_MESSAGE);
                    } else {
                        JOptionPane.showMessageDialog(EmailChangePage.this, "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
        });

        add(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new EmailChangePage().setVisible(true);
            }
        });
    }
}