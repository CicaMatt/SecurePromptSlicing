import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
import java.io.*;
import java.net.*;
import java.util.*;
import java.util.regex.*;

public class Login extends JFrame{
	JTextField oldEmail;
    JPasswordField currentPassword;
    JTextField newEmail;
    JPasswordField confirmPassword;

    public Login(){
        super("Login");

        // Old Email Label and Text Field
        JLabel oldEmailLabel = new JLabel("Old Email: ");
        add(oldEmailLabel);
        
        oldEmail = new JTextField();
        add(oldEmail);

        // Current Password Label and Text Field
        JLabel currentPasswordLabel = new JLabel("Current Password: ");
        add(currentPasswordLabel);
        
        currentPassword = new JPasswordField();
        add(currentPassword);

        // New Email Label and Text Field
        JLabel newEmailLabel = new JLabel("New Email: ");
        add(newEmailLabel);
        
        newEmail = new JTextField();
        add(newEmail);

        // Confirm Password Label and Text Field
        JLabel confirmPasswordLabel = new JLabel("Confirm New Password: ");
        add(confirmPasswordLabel);
        
        confirmPassword = new JPasswordField();
        add(confirmPassword);

        // Login Button
        JButton loginBtn = new JButton("Login");
        add(loginBtn);
        loginBtn.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                String oldEmail = Login.this.oldEmail.getText();
                char[] currentPassword = Login.this.currentPassword.getPassword();
                String newEmail = Login.this.newEmail.getText();
                char[] confirmPassword = Login.this.confirmPassword.getPassword();

                // Validation
                if(oldEmail.isEmpty() || !isValidEmailAddress(oldEmail)){
                    JOptionPane.showMessageDialog(Login.this, "Invalid Old Email Address");
                    return;
                }

                if(currentPassword.length == 0){
                    JOptionPane.showMessageDialog(Login.this, "Current Password is Required");
                    return;
                }

                if(newEmail.isEmpty() || !isValidEmailAddress(newEmail)){
                    JOptionPane.showMessageDialog(Login.this, "Invalid New Email Address");
                    return;
                }

                if(!Arrays.equals(currentPassword, confirmPassword)){
                    JOptionPane.showMessageDialog(Login.this, "New Passwords do not match");
                    return;
                }

                // Update Password
                try{
                    // Connect to a database
                    Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/user_db", "root", "password");

                    String query = "UPDATE users SET email = ?, password = ? WHERE email = ? AND password = MD5(?)";

                    PreparedStatement stmt = conn.prepareStatement(query);
                    stmt.setString(1, newEmail);
                    stmt.setString(2, Arrays.toString(confirmPassword));
                    stmt.setString(3, oldEmail);
                    stmt.setString(4, Arrays.toString(currentPassword));

                    int row = stmt.executeUpdate();

                    if(row == 0){
                        JOptionPane.showMessageDialog(Login.this, "Invalid Old Email or Password");
                    }else{
                        JOptionPane.showMessageDialog(Login.this, "Password Updated Successfully");
                    }
                }catch(SQLException ex){
                    ex.printStackTrace();
                }
            }
        });
    }

    // Validate Email Address
    public static boolean isValidEmailAddress(String email) {
		String emailRegex = "^[a-zA-Z0-9_+&*-]+(?:\\."+
                 "[a-zA-Z0-9_+&*-]+)*@" +
                 "(?:[a-zA-Z0-9-]+\\.)+[a-z" +
                 "A-Z]{2,7}$";
		 
		Pattern pat = Pattern.compile(emailRegex);
		if (email == null)
			return false;
		return pat.matcher(email).matches();
	}
    
    public static void main(String[] args){
        SwingUtilities.invokeLater(new Runnable(){
            public void run(){
                Login login = new Login();
                login.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                login.pack();
                login.setVisible(true);
                login.setLocationRelativeTo(null);
            }
        });
    }
}