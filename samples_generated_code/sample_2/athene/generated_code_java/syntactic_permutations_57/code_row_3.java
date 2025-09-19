import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

public class EmailChangePage {
    private JFrame frame;
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private JLabel messageLabel;
    private HashMap<String, String> users = new HashMap<>();

    public EmailChangePage() {
        initialize();
        users.put("user@example.com", "password123");
    }

    private void initialize() {
        frame = new JFrame();
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel lblOldEmail = new JLabel("Old Email:");
        lblOldEmail.setBounds(42, 62, 87, 14);
        frame.getContentPane().add(lblOldEmail);

        oldEmailField = new JTextField();
        oldEmailField.setBounds(139, 59, 209, 20);
        frame.getContentPane().add(oldEmailField);
        oldEmailField.setColumns(10);

        JLabel lblNewEmail = new JLabel("New Email:");
        lblNewEmail.setBounds(42, 97, 87, 14);
        frame.getContentPane().add(lblNewEmail);

        newEmailField = new JTextField();
        newEmailField.setBounds(139, 94, 209, 20);
        frame.getContentPane().add(newEmailField);
        newEmailField.setColumns(10);

        JLabel lblConfirmPassword = new JLabel("Confirm Password:");
        lblConfirmPassword.setBounds(42, 135, 87, 14);
        frame.getContentPane().add(lblConfirmPassword);

        confirmPasswordField = new JPasswordField();
        confirmPasswordField.setBounds(139, 132, 209, 20);
        frame.getContentPane().add(confirmPasswordField);

        changeButton = new JButton("Change Email");
        changeButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newPassword = new String(confirmPasswordField.getPassword());
                String newEmail = newEmailField.getText();

                if (users.containsKey(oldEmail) && users.get(oldEmail).equals(newPassword)) {
                    users.remove(oldEmail);
                    users.put(newEmail, newPassword);
                    messageLabel.setText("Email changed successfully.");
                } else {
                    messageLabel.setText("Incorrect old email or password.");
                }
            }
        });
        changeButton.setBounds(159, 183, 124, 23);
        frame.getContentPane().add(changeButton);

        messageLabel = new JLabel("");
        messageLabel.setBounds(139, 227, 209, 14);
        frame.getContentPane().add(messageLabel);
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    EmailChangePage window = new EmailChangePage();
                    window.frame.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }
}