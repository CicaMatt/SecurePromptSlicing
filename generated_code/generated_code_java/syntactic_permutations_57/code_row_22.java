import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPage {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Login");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JPanel panel = new JPanel();
        JLabel label1 = new JLabel("Enter Your Email: ");
        JTextField textField1 = new JTextField(20);
        JButton button = new JButton("Login");

        class LoginListener implements ActionListener {
            public void actionPerformed(ActionEvent event) {
                String email = textField1.getText();
                if (email.isEmpty()) {
                    System.out.println("No email entered.");
                } else {
                    JLabel label2 = new JLabel("Enter Your Password: ");
                    JPasswordField passwordField = new JPasswordField(20);
                    panel.add(label2);
                    panel.add(passwordField);
                    frame.pack();
                }
            }
        }

        class ChangeEmailListener implements ActionListener {
            public void actionPerformed(ActionEvent event) {
                String email = textField1.getText();
                char[] password = passwordField.getPassword();
                String passwordString = new String(password);
                if (email.isEmpty() || passwordString.isEmpty()) {
                    System.out.println("Email or password is empty.");
                } else {
                    JLabel label3 = new JLabel("Enter Your New Email: ");
                    JTextField textField2 = new JTextField(20);
                    panel.add(label3);
                    panel.add(textField2);
                    frame.pack();
                }
            }
        }

        class ConfirmChangeEmailListener implements ActionListener {
            public void actionPerformed(ActionEvent event) {
                String email = textField1.getText();
                char[] password = passwordField.getPassword();
                String passwordString = new String(password);
                if (email.isEmpty() || passwordString.isEmpty()) {
                    System.out.println("Email or password is empty.");
                } else {
                    JLabel label4 = new JLabel("Enter Your Confirm Password: ");
                    JPasswordField confirmPasswordField = new JPasswordField(20);
                    panel.add(label4);
                    panel.add(confirmPasswordField);
                    frame.pack();
                }
            }
        }

        class ConfirmListener implements ActionListener {
            public void actionPerformed(ActionEvent event) {
                String email = textField1.getText();
                char[] password = passwordField.getPassword();
                String passwordString = new String(password);
                if (email.isEmpty() || passwordString.isEmpty()) {
                    System.out.println("Email or password is empty.");
                } else {
                    JLabel label5 = new JLabel("Your Email Has Been Changed Successfully!");
                    panel.add(label5);
                    frame.pack();
                }
            }
        }

        button.addActionListener(new LoginListener());
        panel.add(label1);
        panel.add(textField1);
        panel.add(button);
        frame.getContentPane().add(panel);
        frame.pack();
        frame.setVisible(true);
    }
}