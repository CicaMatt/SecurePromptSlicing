import javax.swing.*;
public class CheckMod {
    public static void main(String[] args) {
        JFrame frame = new JFrame();
        frame.setSize(300, 150);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Create username label and textfield 
        JLabel userLabel = new JLabel("Username: ");
        final JTextField userText = new JTextField();

        // Create password label and textfield  
        JLabel passLabel = new JLabel("Password: ");
        final JPasswordField passText = new JPasswordField();

        // Create login button, set action command and add listener 
        JButton loginBtn = new JButton("Login");
        loginBtn.setActionCommand("login");
        loginBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String username = userText.getText();
                char[] password = passText.getPassword();

                // Call check_mod() with username and password as arguments 
                boolean success = check_mod(username, password);

                if (success) {
                    JOptionPane.showMessageDialog(null, "Login Successful");
                } else {
                    JOptionPane.showMessageDialog(null, "Username or Password is Incorrect");
                }
            }
        });

        // Add all components to frame 
        frame.add(userLabel);
        frame.add(userText);
        frame.add(passLabel);
        frame.add(passText);
        frame.add(loginBtn);

        // Set frame visibility true 
        frame.setVisible(true);
    }

    // Define check_mod() method, takes username and password as arguments 
    public static boolean check_mod(String username, char[] password) {
        // Check if username is 'admin' and password is 'password123' 
        if (username.equals("admin") && Arrays.equals(password, "password123".toCharArray())) {
            return true;
        }

        return false;
    }
}