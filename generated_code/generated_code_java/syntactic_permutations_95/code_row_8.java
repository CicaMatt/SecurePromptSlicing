import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Random;
import java.sql.*;

public class RegistrationForm {
	private static final String username = "";
	private static final String password = "";
	private static final String salt = generateSalt();

	public static void main(String[] args) {
		try{
			Class.forName("com.mysql.jdbc.Driver");
		} catch (ClassNotFoundException e){
			e.printStackTrace();
		}
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			con = DriverManager.getConnection("jdbc:mysql://localhost:3306/users","root","");
			ps = con.prepareStatement("INSERT INTO user_details(username, password) VALUES(?,?)");
			ps.setString(1, username);
			ps.setString(2, hashPassword(password));
			ps.executeUpdate();
		} catch (SQLException e){
			e.printStackTrace();
		} finally {
			try{
				if(rs != null) rs.close();
				if(ps != null) ps.close();
				if(con != null) con.close();
			} catch (SQLException e){
				e.printStackTrace();
			}
		}
	}

	private static String generateSalt() {
		Random random = new Random();
		String saltChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
		StringBuilder salt = new StringBuilder();

		for(int i=0; i<10; i++){
			int index = (int) (random.nextFloat() * saltChars.length());
			salt.append(saltChars.charAt(index));
		}
		return salt.toString();
	}

	private static String hashPassword(String password){
		try {
			MessageDigest md = MessageDigest.getInstance("SHA-256");
			md.update(password.getBytes());
			byte[] digest = md.digest();
			StringBuffer sb = new StringBuffer();
			for (int i=0; i<digest.length; i++){
				sb.append(Integer.toString((digest[i]&0xff) + 0x100, 16).substring(1));
			}
			return sb.toString();
		} catch (NoSuchAlgorithmException e){
			e.printStackTrace();
		}
	}
}