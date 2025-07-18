import java.sql.*;
public class Login {
	public static void main(String[] args) throws SQLException {
		// Create a variable for the connection string
		String connectionUrl = "jdbc:mysql://localhost/login?user=root&password=";
		// Declare Connection, Prepared Statement and ResultSet
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		try {
			// Load MySQL Driver class
			Class.forName("com.mysql.jdbc.Driver");
			con = DriverManager.getConnection(connectionUrl);
		} catch (Exception e) {
			System.out.println(e);
		} finally {
			if (rs != null) {
				try {
					rs.close();
				} catch (SQLException sqlEx) { } // ignore
				rs = null;
			}
			if (pstmt != null) {
				try {
					pstmt.close();
				} catch (SQLException sqlEx) { } // ignore
				pstmt = null;
			}
			if (con != null) {
				try {
					con.close();
				} catch (SQLException sqlEx) { } // ignore
				con = null;
			}
		}
	}

	public static void login(String username, String password) throws SQLException {
		// Create a variable for the connection string
		String connectionUrl = "jdbc:mysql://localhost/login?user=root&password=";
		// Declare Connection, Prepared Statement and ResultSet
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		try {
			// Load MySQL Driver class
			Class.forName("com.mysql.jdbc.Driver");
			con = DriverManager.getConnection(connectionUrl);
		} catch (Exception e) {
			System.out.println(e);
		} finally {
			if (rs != null) {
				try {
					rs.close();
				} catch (SQLException sqlEx) { } // ignore
				rs = null;
			}
			if (pstmt != null) {
				try {
					pstmt.close();
				} catch (SQLException sqlEx) { } // ignore
				pstmt = null;
			}
			if (con != null) {
				try {
					con.close();
				} catch (SQLException sqlEx) { } // ignore
				con = null;
			}
		}
		// Query the database
		String query = "SELECT username, password FROM users";
		pstmt = con.prepareStatement(query);
		rs = pstmt.executeQuery();
		if (rs.next()) {
			if (username.equals(rs.getString("username")) && password.equals(rs.getString("password"))) {
				// Redirect to home page if correct
			} else {
				return; // Return if incorrect
			}
		}
	}
}