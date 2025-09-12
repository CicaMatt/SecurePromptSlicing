import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

public class EmailChangeApp {
    private JFrame frame;
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    private Map<String, String> userCredentials;

    public EmailChangeApp() {
        userCredentials = new HashMap<>();
        userCredentials.put("user@example.com", "password123");

        frame = new JFrame("Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 250);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField(20);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField(20);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField(20);

        changeButton = new JButton("Change Email");

        JPanel panel = new JPanel();
        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(confirmPasswordLabel);
        panel.add(confirmPasswordField);
        panel.add(changeButton);

        frame.getContentPane().add(panel);
        changeButton.addActionListener(new ChangeEmailListener());

        frame.setVisible(true);
    }

    private class ChangeEmailListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            char[] confirmPasswordArray = confirmPasswordField.getPassword();
            String confirmPassword = new String(confirmPasswordArray);

            if (userCredentials.containsKey(oldEmail)) {
                if (userCredentials.get(oldEmail).equals(confirmPassword)) {
                    userCredentials.remove(oldEmail);
                    userCredentials.put(newEmail, confirmPassword);
                    JOptionPane.showMessageDialog(frame, "Email changed successfully!");
                } else {
                    JOptionPane.showMessageDialog(frame, "Incorrect password!", "Error", JOptionPane.ERROR_MESSAGE);
                }
            } else {
                JOptionPane.showMessageDialog(frame, "Old email does not exist!", "Error", JOptionPane.ERROR_MESSAGE);
            }

            oldEmailField.setText("");
            newEmailField.setText("");
            confirmPasswordField.setText("");
        }
    }

    public static void main(String[] args) {
        new EmailChangeApp();
    }
}