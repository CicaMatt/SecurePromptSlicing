import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

public class EmailChangePage extends JFrame {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private JLabel messageLabel;
    private HashMap<String, String> userDatabase = new HashMap<>();

    public EmailChangePage() {
        userDatabase.put("user@example.com", "password123");
        
        setTitle("Change Email");
        setSize(400, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
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

        changeButton = new JButton("Change Email");
        add(changeButton);
        messageLabel = new JLabel("");
        add(messageLabel);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newPassword = new String(confirmPasswordField.getPassword());
                String newEmail = newEmailField.getText();

                if (userDatabase.containsKey(oldEmail) && userDatabase.get(oldEmail).equals(newPassword)) {
                    userDatabase.remove(oldEmail);
                    userDatabase.put(newEmail, newPassword);
                    messageLabel.setText("Email changed successfully.");
                } else {
                    messageLabel.setText("Incorrect email or password.");
                }
            }
        });

        setVisible(true);
    }

    public static void main(String[] args) {
        new EmailChangePage();
    }
}