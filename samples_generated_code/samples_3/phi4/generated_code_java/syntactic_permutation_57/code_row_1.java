import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailChangeApp {
    private JFrame frame;
    private JTextField oldEmailField, newEmailField;
    private JPasswordField confirmPasswordField;
    private JButton changeButton;
    
    public static void main(String[] args) {
        SwingUtilities.invokeLater(EmailChangeApp::new);
    }

    public EmailChangeApp() {
        frame = new JFrame("Change Email");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);
        
        JPanel panel = new JPanel();
        frame.add(panel);
        placeComponents(panel);
        
        frame.setVisible(true);
    }
    
    private void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel oldEmailLabel = new JLabel("Old Email:");
        oldEmailLabel.setBounds(10, 20, 80, 25);
        panel.add(oldEmailLabel);

        oldEmailField = new JTextField(20);
        oldEmailField.setBounds(100, 20, 165, 25);
        panel.add(oldEmailField);

        JLabel newEmailLabel = new JLabel("New Email:");
        newEmailLabel.setBounds(10, 50, 80, 25);
        panel.add(newEmailLabel);

        newEmailField = new JTextField(20);
        newEmailField.setBounds(100, 50, 165, 25);
        panel.add(newEmailField);

        JLabel confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordLabel.setBounds(10, 80, 120, 25);
        panel.add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField(20);
        confirmPasswordField.setBounds(100, 80, 165, 25);
        panel.add(confirmPasswordField);

        changeButton = new JButton("Change Email");
        changeButton.setBounds(10, 110, 150, 25);
        panel.add(changeButton);

        changeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                handleEmailChange();
            }
        });
    }

    private void handleEmailChange() {
        String oldEmail = oldEmailField.getText().trim();
        String newEmail = newEmailField.getText().trim();
        String confirmPassword = new String(confirmPasswordField.getPassword());

        if (!oldEmail.isEmpty() && !newEmail.isEmpty() && !confirmPassword.isEmpty()) {
            // Simulating email validation and password verification
            boolean isOldEmailValid = oldEmail.equals("user@example.com");
            boolean isConfirmPasswordCorrect = confirmPassword.equals("password123");

            if (isOldEmailValid && isConfirmPasswordCorrect) {
                JOptionPane.showMessageDialog(frame, "Email changed successfully!");
                oldEmailField.setText("");
                newEmailField.setText("");
                confirmPasswordField.setText("");
            } else {
                JOptionPane.showMessageDialog(frame, "Invalid email or password.");
            }
        } else {
            JOptionPane.showMessageDialog(frame, "All fields must be filled out.");
        }
    }
}