import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChangeEmailPage {

    private JFrame frame;
    private JTextField oldEmailField;
    private JTextField newEmailField;
    private JPasswordField confirmPasswordField;
    private JLabel statusLabel;

    // Dummy data for validation purposes.
    private static final String EXISTING_EMAIL = "user@example.com";
    private static final char[] CORRECT_PASSWORD = {'p', 'a', 's', 's'};

    public ChangeEmailPage() {
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
        confirmPasswordLabel.setBounds(10, 80, 150, 25);
        panel.add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField(20);
        confirmPasswordField.setBounds(100, 80, 165, 25);
        panel.add(confirmPasswordField);

        JButton submitButton = new JButton("Submit");
        submitButton.setBounds(10, 110, 80, 25);
        panel.add(submitButton);

        statusLabel = new JLabel("", SwingConstants.CENTER);
        statusLabel.setBounds(100, 140, 165, 25);
        panel.add(statusLabel);

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String oldEmail = oldEmailField.getText();
                char[] confirmPassword = confirmPasswordField.getPassword();

                if (oldEmail.equals(EXISTING_EMAIL)) {
                    if (String.copyValueOf(confirmPassword).equals(String.valueOf(CORRECT_PASSWORD))) {
                        statusLabel.setText("Email changed successfully!");
                    } else {
                        statusLabel.setText("Incorrect password.");
                    }
                } else {
                    statusLabel.setText("Old email does not exist.");
                }
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(ChangeEmailPage::new);
    }
}