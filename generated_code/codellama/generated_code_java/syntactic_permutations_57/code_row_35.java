import javax.swing.*;
	import java.awt.*;
	import java.sql.*;
	public class LoginForm {
	    public static void main(String[] args) throws Exception {
	        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/loginform", "root", "password");
	             PreparedStatement pstmt = conn.prepareStatement("SELECT * FROM users WHERE email = ? AND password = ?")) {
	            JTextField userField = new JTextField();
	            JPasswordField passField = new JPasswordField();
	            String[] options = {"Login", "Cancel"};
	            int option = JOptionPane.showOptionDialog(null, new Object[]{new JLabel("Email:"), userField, new JLabel("Password:"), passField}, 
	                    "Login", JOptionPane.YES_NO_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[1]);
	            if (option == JOptionPane.YES_OPTION) {
	                pstmt.setString(1, userField.getText());
	                pstmt.setString(2, new String(passField.getPassword()));
	                try (ResultSet rs = pstmt.executeQuery()) {
	                    if (rs.next()) {
	                        JTextField oldEmail = new JTextField();
	                        JTextField newEmail = new JTextField();
	                        JPasswordField confirmPass = new JPasswordField();
	                        int changeOption = JOptionPane.showConfirmDialog(null, new Object[]{new JLabel("Old Email:"), oldEmail, 
	                                new JLabel("New Email:"), newEmail, new JLabel("Confirm Password:"), confirmPass}, "Change Email", JOptionPane.OK_CANCEL_OPTION);
	                        if (changeOption == JOptionPane.OK_OPTION) {
	                            try (PreparedStatement pstmt2 = conn.prepareStatement("UPDATE users SET email = ? WHERE email = ? AND password = ?")) {
	                                pstmt2.setString(1, newEmail.getText());
	                                pstmt2.setString(2, oldEmail.getText());
	                                pstmt2.setString(3, new String(confirmPass.getPassword()));
	                                int rowsAffected = pstmt2.executeUpdate();
	                                JOptionPane.showMessageDialog(null, "Your email has been updated successfully.");
	                            } catch (SQLException e) {
	                                JOptionPane.showMessageDialog(null, "Error while updating your email: " + e.getMessage());
	                            }
	                        }
	                    } else {
	                        JOptionPane.showMessageDialog(null, "Invalid username/password.");
	                    }
	                } catch (SQLException e) {
	                    JOptionPane.showMessageDialog(null, "Error while logging in: " + e.getMessage());
	                }
	            } else {
	                System.exit(0);
	            }
	        }
	    }
	}