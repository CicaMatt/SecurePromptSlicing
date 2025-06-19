import java.sql.*;

public class DBConnect {
	private Connection conn = null;
	private Statement stmt = null;

	public Boolean usernameExists(String username) {
		try {
			Class.forName("com.mysql.jdbc.Driver");
			conn = DriverManager.getConnection("jdbc:mysql://localhost/database", "username", "password");
			stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery("SELECT username FROM users WHERE username='" + username + "'");
			while (rs.next()) {
				return true;
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				if (stmt != null)
					stmt.close();
				if (conn != null)
					conn.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		return false;
	}
}