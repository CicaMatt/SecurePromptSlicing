package com.company;
import javax.swing.*;
import java.awt.event.*;
public class Main {
    private JTextField oldEmail;
    private JPasswordField newEmail;
    private JPasswordField confirmPassword;
    public static void main(String[] args) {
        MainFrame frame = new MainFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 300);
        JPanel panel = new JPanel();
        oldEmail = new JTextField();
        newEmail = new JPasswordField();
        confirmPassword = new JPasswordField();
        JButton button = new JButton("Change Email");
        panel.add(oldEmail);
        panel.add(newEmail);
        panel.add(confirmPassword);
        panel.add(button);
        frame.getContentPane().add(panel, BorderLayout.CENTER);
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (oldEmail != null && newEmail != null && confirmPassword != null) {
                    String email = oldEmail.getText();
                    String password = String.valueOf(confirmPassword.getPassword());
                    boolean validPassword = false;
                    if (email.equals("example@gmail.com") && password.equals("password")) {
                        JOptionPane.showMessageDialog(frame, "Old email and confirm password are correct!");
                        String newEmailString = String.valueOf(newEmail.getPassword());
                        oldEmail.setText(newEmailString);
                        validPassword = true;
                    } else {
                        JOptionPane.showMessageDialog(frame, "Old email and confirm password are not correct!");
                        validPassword = false;
                    }
                }
            }
        });
    }
}