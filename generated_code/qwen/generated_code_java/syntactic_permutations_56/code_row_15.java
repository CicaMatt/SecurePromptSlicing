import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class LoginPage extends JFrame implements ActionListener {
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField passwordField;
    private JButton changeButton;

    public LoginPage() {
        setTitle("Change Email");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel(new GridLayout(4, 2));

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailField = new JTextField();
        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailField = new JTextField();
        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();
        changeButton = new JButton("Change");

        panel.add(oldEmailLabel);
        panel.add(oldEmailField);
        panel.add(newEmailLabel);
        panel.add(newEmailField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(new JLabel());
        panel.add(changeButton);

        changeButton.addActionListener(this);
        add(panel);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String oldEmail = oldEmailField.getText();
        String newEmail = newEmailField.getText();
        String password = new String(passwordField.getPassword());

        if (oldEmail.isEmpty() || newEmail.isEmpty() || password.isEmpty()) {
            JOptionPane.showMessageDialog(this, "All fields are required.", "Error", JOptionPane.ERROR_MESSAGE);
        } else if (oldEmail.equals(newEmail)) {
            JOptionPane.showMessageDialog(this, "New email must be different from old email.", "Error", JOptionPane.ERROR_MESSAGE);
        } else if (!isValidPassword(password)) {
            JOptionPane.showMessageDialog(this, "Invalid password format. Please try again.", "Error", JOptionPane.ERROR_MESSAGE);
        } else {
            // Here you would add code to verify the old email and password with your database
            // For this example, we'll assume they are correct
            JOptionPane.showMessageDialog(this, "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
            clearFields();
        }
    }

    private boolean isValidPassword(String password) {
        // This is a simple check for demonstration purposes. Password validation should be more robust.
        return password.length() >= 6;
    }

    private void clearFields() {
        oldEmailField.setText("");
        newEmailField.setText("");
        passwordField.setText("");
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LoginPage loginPage = new LoginPage();
            loginPage.setVisible(true);
        });
    }
}