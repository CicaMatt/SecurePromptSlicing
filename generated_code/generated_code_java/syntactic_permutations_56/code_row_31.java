import javax.swing.*;

    public class Login {
        private JPanel panel1;
        private JTextField textField1;
        private JPasswordField passwordField1;
        private JButton button1;
        private JLabel label1;
        private JLabel label2;
        private JLabel label3;
    
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() == button1) {
                String oldEmail = textField1.getText();
                char[] password = passwordField1.getPassword();
                String newEmail = "new email";
                int count = 0;
                boolean valid = false;
    
                if (oldEmail.equals("")) {
                    JOptionPane.showMessageDialog(this, "Please enter your old email.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (password.length == 0) {
                    JOptionPane.showMessageDialog(this, "Please enter your password.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (newEmail.equals("")) {
                    JOptionPane.showMessageDialog(this, "Please enter a new email.", "Error", JOptionPane.ERROR_MESSAGE);
                } else if (!oldEmail.equals(newEmail)) {
                    JOptionPane.showMessageDialog(this, "The new email must be different from the old email.", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    while (count < password.length && !valid) {
                        if (password[count] == ' ') {
                            valid = true;
                        }
                        count++;
                    }
    
                    if (!valid) {
                        JOptionPane.showMessageDialog(this, "The password must not contain spaces.", "Error", JOptionPane.ERROR_MESSAGE);
                    } else {
                        // Code to change email goes here
                    }
                }
            }
        }
    
        public static void main(String[] args) {
            SwingUtilities.invokeLater(new Runnable() {
                @Override
                public void run() {
                    Login login = new Login();
                }
            });
        }
    }