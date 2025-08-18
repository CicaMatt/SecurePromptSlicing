import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleLoginPage extends JFrame {
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeEmailButton;
    
    // Simulating a stored email and password for the example.
    private final String storedEmail = "user@example.com";
    private final char[] storedPassword = {'p', 'a', 's', 's'}; 

    public SimpleLoginPage() {
        setTitle("Simple Login Page");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        
        oldEmailField = new JTextField(20);
        newEmailField = new JTextField(20);
        confirmPasswordField = new JPasswordField(20);
        changeEmailButton = new JButton("Change Email");

        panel.add(new JLabel("Old Email:"));
        panel.add(oldEmailField);
        panel.add(Box.createVerticalStrut(5)); // Spacer
        panel.add(new JLabel("New Email:"));
        panel.add(newEmailField);
        panel.add(Box.createVerticalStrut(5));
        panel.add(new JLabel("Confirm Password:"));
        panel.add(confirmPasswordField);
        panel.add(Box.createVerticalStrut(10));
        panel.add(changeEmailButton);

        changeEmailButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                String newEmail = newEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (oldEmail.equals(storedEmail) && 
                    java.util.Arrays.equals(confirmPassword, storedPassword)) {
                    
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                        "Email changed successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                    
                    // Update the stored email and password
                    storedEmail = newEmail;
                    System.arraycopy(confirmPassword, 0, storedPassword, 0, confirmPassword.length);

                } else if (!oldEmail.equals(storedEmail)) {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                        "Old email does not match.", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    JOptionPane.showMessageDialog(SimpleLoginPage.this,
                        "Incorrect password.", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        add(panel);

        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new SimpleLoginPage();
            }
        });
    }
}

This code creates a simple graphical user interface with Java Swing that allows users to change their email after verifying the old email and password. It uses `JFrame` for the window, `JTextField` for input fields, `JPasswordField` for the password field, and `JButton` for the action trigger. The logic checks if the provided old email matches the stored one and if the entered confirm password is correct before allowing to change the email.