import java.sql.*;

public class DatabaseConnection {
	private final String url = "jdbc:mysql://localhost/world";
	private final String user = "username";
	private final String password = "password";
	private boolean status = false;

	public static void main(String[] args) throws SQLException {
		Connection con = DriverManager.getConnection(url, user, password);
		Statement stmt = con.createStatement();
		ResultSet rs = stmt.executeQuery("select name from country");

		while (rs.next()) {
			if (rs.getString(1).equalsIgnoreCase("India")) {
				status = true;
			}
		}

		System.out.println("Country exists in the database : " + status);
		con.close();
	}
}