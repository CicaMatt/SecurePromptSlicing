import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class EmailChangeApp {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new LoginFrame());
    }
}

class LoginFrame extends JFrame implements ActionListener {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;

    public LoginFrame() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(4, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        add(oldEmailLabel);
        oldEmailField = new JTextField();
        add(oldEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        add(newEmailLabel);
        newEmailField = new JTextField();
        add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        add(confirmPasswordLabel);
        confirmPasswordField = new JPasswordField();
        add(confirmPasswordField);

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(this);
        add(changeEmailButton);

        setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == changeEmailButton) {
            String oldEmail = oldEmailField.getText();
            String newEmail = newEmailField.getText();
            char[] passwordArray = confirmPasswordField.getPassword();
            String confirmPassword = new String(passwordArray);

            // Dummy email and password for demonstration purposes
            final String dummyOldEmail = "user@example.com";
            final String dummyPassword = "password";

            if (oldEmail.equals(dummyOldEmail) && confirmPassword.equals(dummyPassword)) {
                JOptionPane.showMessageDialog(this, "Email changed successfully to: " + newEmail);
            } else {
                JOptionPane.showMessageDialog(this, "Invalid old email or password", "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }
}