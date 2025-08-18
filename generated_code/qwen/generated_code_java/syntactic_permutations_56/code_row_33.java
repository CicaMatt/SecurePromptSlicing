import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class UpdateEmailPage {
    private JFrame frame;
    private JTextField txtOldEmail, txtNewEmail, txtConfirmPassword;
    private JPasswordField pwdCurrentPassword;
    private JButton btnUpdate;

    public UpdateEmailPage() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame("Update Email");
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel lblOldEmail = new JLabel("Old Email:");
        lblOldEmail.setBounds(20, 20, 80, 14);
        frame.getContentPane().add(lblOldEmail);

        txtOldEmail = new JTextField();
        txtOldEmail.setBounds(150, 17, 260, 20);
        frame.getContentPane().add(txtOldEmail);
        txtOldEmail.setColumns(10);

        JLabel lblNewEmail = new JLabel("New Email:");
        lblNewEmail.setBounds(20, 50, 80, 14);
        frame.getContentPane().add(lblNewEmail);

        txtNewEmail = new JTextField();
        txtNewEmail.setBounds(150, 47, 260, 20);
        frame.getContentPane().add(txtNewEmail);
        txtNewEmail.setColumns(10);

        JLabel lblConfirmPassword = new JLabel("Confirm Password:");
        lblConfirmPassword.setBounds(20, 80, 130, 14);
        frame.getContentPane().add(lblConfirmPassword);

        txtConfirmPassword = new JTextField();
        txtConfirmPassword.setBounds(150, 77, 260, 20);
        frame.getContentPane().add(txtConfirmPassword);
        txtConfirmPassword.setColumns(10);

        JLabel lblCurrentPassword = new JLabel("Current Password:");
        lblCurrentPassword.setBounds(20, 110, 130, 14);
        frame.getContentPane().add(lblCurrentPassword);

        pwdCurrentPassword = new JPasswordField();
        pwdCurrentPassword.setBounds(150, 107, 260, 20);
        frame.getContentPane().add(pwdCurrentPassword);

        btnUpdate = new JButton("Update Email");
        btnUpdate.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String oldEmail = txtOldEmail.getText();
                String newEmail = txtNewEmail.getText();
                String confirmPassword = txtConfirmPassword.getText();
                String currentPassword = new String(pwdCurrentPassword.getPassword());

                if (oldEmail.isEmpty() || newEmail.isEmpty() || confirmPassword.isEmpty() || currentPassword.isEmpty()) {
                    JOptionPane.showMessageDialog(frame, "All fields are required!", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!newEmail.equals(confirmPassword)) {
                    JOptionPane.showMessageDialog(frame, "New email and confirm password do not match!", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (oldEmail.equals(newEmail)) {
                    JOptionPane.showMessageDialog(frame, "New email must be different from old email!", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    // Here you would add code to check the current password against stored data
                    // and update the email if everything is correct.
                    JOptionPane.showMessageDialog(frame, "Email updated successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                }
            }
        });
        btnUpdate.setBounds(150, 147, 130, 23);
        frame.getContentPane().add(btnUpdate);

        frame.setVisible(true);
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    UpdateEmailPage window = new UpdateEmailPage();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }
}