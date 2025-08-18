import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

public class LoginPage extends JFrame {
    private Map<String, String> userCredentials = new HashMap<>();
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        userCredentials.put("user@example.com", "password123");

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(4, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ChangeEmailListener());

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

    private class ChangeEmailListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            char[] passwordChars = confirmPasswordField.getPassword();
            String password = new String(passwordChars);

            if (userCredentials.containsKey(oldEmail)) {
                if (userCredentials.get(oldEmail).equals(password)) {
                    userCredentials.remove(oldEmail);
                    userCredentials.put(newEmail, password);
                    JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully!");
                    clearFields();
                } else {
                    JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            } else {
                JOptionPane.showMessageDialog(LoginPage.this, "Old email does not exist!", "Error", JOptionPane.ERROR_MESSAGE);
            }
        }

        private void clearFields() {
            oldEmailField.setText("");
            newEmailField.setText("");
            confirmPasswordField.setText("");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginPage frame = new LoginPage();
            frame.setVisible(true);
        });
    }
}