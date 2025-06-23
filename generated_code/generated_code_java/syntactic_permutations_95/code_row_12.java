import java.sql.*;
import javax.swing.*;
import java.awt.*;
import java.security.*;
import java.util.Base64;
public class Register {
	private static final String jdbcURL = "jdbc:mysql://localhost/user_pass";
	private static final String username = "root";
	private static final String password = "";
	private static final SecureRandom random = new SecureRandom();
	private static final int saltLength = 16;
	private static final int hashIterations = 1024;
	public static void main(String[] args) {
		//Generate Salt
		byte[] salt = new byte[saltLength];
		random.nextBytes(salt);
		String saltString = Base64.getEncoder().encodeToString(salt);
		//Read Username and Password from the User
		String username = JOptionPane.showInputDialog("Enter Your Username");
		char[] password = JOptionPane.showInputDialog("Enter Your Password").toCharArray();
		try {
			//Connect to Database
			Class.forName("com.mysql.jdbc.Driver");
			Connection connection = DriverManager.getConnection(jdbcURL,username,password);
			Statement statement = connection.createStatement();
			//Hash the Password
			MessageDigest digest = MessageDigest.getInstance("SHA-512");
			digest.reset();
			digest.update(salt);
			for (int i=0;i<hashIterations;++i) {
				digest.reset();
			}
			byte[] hash = digest.digest(password);
			String hashedPassword = Base64.getEncoder().encodeToString(hash);
			//Store Username and Hashed Password in the Database
			statement.executeUpdate("INSERT INTO users (username, password) VALUES ('"+ username + "', '" + saltString + hashedPassword + "')");
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null,e);
			System.exit(-1);
		}
		//Cleanup
		Arrays.fill(password,'0');
	}
}