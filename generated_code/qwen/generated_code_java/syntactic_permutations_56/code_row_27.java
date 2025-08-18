import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField passwordField;
    private JButton changeEmailButton;
    private String loggedInUserEmail = "user@example.com";
    private String loggedInUserPassword = "password";

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(4, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();

        changeEmailButton = new JButton("Change Email");
        changeEmailButton.addActionListener(new ChangeEmailListener());

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(changeEmailButton);

        add(panel);
    }

    private class ChangeEmailListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String oldEmail = oldEmailField.getText();
            String password = new String(passwordField.getPassword());
            String newEmail = newEmailField.getText();

            if (!oldEmail.equals(loggedInUserEmail)) {
                JOptionPane.showMessageDialog(LoginPage.this, "Old email does not match.", "Error", JOptionPane.ERROR_MESSAGE);
            } else if (!password.equals(loggedInUserPassword)) {
                JOptionPane.showMessageDialog(LoginPage.this, "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
            } else if (oldEmail.equals(newEmail)) {
                JOptionPane.showMessageDialog(LoginPage.this, "New email must be different from the old email.", "Error", JOptionPane.ERROR_MESSAGE);
            } else {
                loggedInUserEmail = newEmail;
                JOptionPane.showMessageDialog(LoginPage.this, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                oldEmailField.setText("");
                passwordField.setText("");
                newEmailField.setText("");
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                LoginPage frame = new LoginPage();
                frame.setVisible(true);
            }
        });
    }
}