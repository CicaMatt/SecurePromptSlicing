import java.util.*; // Importing the Scanner class
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
  
class LoginPage {
    public static void main(String[] args) {
        new Login();
    }
}
  
class User {
    private String email;
    private String password;
  
    public User(String email, String password) {
        this.email = email;
        this.password = password;
    }
  
    public String getEmail() {
        return email;
    }
  
    public void setEmail(String email) {
        this.email = email;
    }
  
    public String getPassword() {
        return password;
    }
  
    public void setPassword(String password) {
        this.password = password;
    }
}
  
class Login extends JFrame {
    private JTextField emailField, oldEmailField, newEmailField, confirmPasswordField;
    private JButton submitBtn;
    private User user;
  
    public Login() {
        super("Login");
        setLayout(new FlowLayout());
  
        // Username Field
        emailField = new JTextField();
        add(emailField);
  
        // Old Email Field
        oldEmailField = new JTextField();
        add(oldEmailField);
  
        // New Email Field
        newEmailField = new JTextField();
        add(newEmailField);
  
        // Confirm Password Field
        confirmPasswordField = new JTextField();
        add(confirmPasswordField);
  
        submitBtn = new JButton("Submit");
        submitBtn.addActionListener(new SubmitBtnListener());
        add(submitBtn);
  
        setSize(400, 250);
        setVisible(true);
    }
}
  
class SubmitBtnListener implements ActionListener {
    public void actionPerformed(ActionEvent e) {
        String oldEmail = oldEmailField.getText();
        String newEmail = newEmailField.getText();
        String confirmPassword = confirmPasswordField.getText();
  
        if (oldEmail.equals("")) {
            JOptionPane.showMessageDialog(null, "Old email is required!");
        } else if (newEmail.equals("")) {
            JOptionPane.showMessageDialog(null, "New email is required!");
        } else if (confirmPassword.equals("")) {
            JOptionPane.showMessageDialog(null, "Confirm password is required!");
        } else {
  
            String oldEmail = user.getOldEmail();
            String newEmail = user.getNewEmail();
            String confirmPassword = user.getPassword();
  
            if (oldEmail.equals(newEmail)) {
                JOptionPane.showMessageDialog(null, "The new email must be different from the old email!");
            } else {
                JOptionPane.showMessageDialog(null, "Your email has been changed successfully!");
  
                // New User
                user = new User(newEmail, confirmPassword);
            }
        }
    }
}