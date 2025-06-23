import java.sql.*;

public class Stock {
	// JDBC driver name and database URL
	static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
	static final String DATABASE_URL = "jdbc:mysql://localhost/stock";

	//  Database credentials
	static final String USER = "username";
	static final String PASS = "password";

	public static void buy_stock(String stockName, int quantity) {
		Connection conn = null;
		PreparedStatement preparedStatement = null;
		try {
			// Register JDBC driver
			Class.forName("com.mysql.jdbc.Driver");

			// Open a connection
			System.out.println("Connecting to database...");
			conn = DriverManager.getConnection(DATABASE_URL, USER, PASS);

			String sql = "INSERT INTO stock VALUES (?, ?)";
			preparedStatement = conn.prepareStatement(sql);
			preparedStatement.setString(1, stockName);
			preparedStatement.setInt(2, quantity);

			// Execute the prepared statement
			System.out.println("Inserting record into stock table...");
			preparedStatement.executeUpdate();
			System.out.println("Record inserted successfully");

		} catch (SQLException e) {
			throw new IllegalStateException(e);
		} finally {
			if (conn != null) {
				try {
					conn.close();
				} catch (SQLException e) {
					System.err.format("SQL State: %s\n%s", e.getSQLState(), e.getMessage());
				}
			}
		}

	}

	public static void buy_function(String stockName) {
		// Connect to the database and get a connection object
		Connection conn = null;
		PreparedStatement preparedStatement = null;

		try {
			Class.forName("com.mysql.jdbc.Driver");
			System.out.println("Connecting to a selected database...");
			conn = DriverManager.getConnection(DATABASE_URL, USER, PASS);

			String sql = "SELECT quantity FROM stock WHERE name = ?";
			preparedStatement = conn.prepareStatement(sql);
			preparedStatement.setString(1, stockName);

			// Execute the prepared statement and get a result set object
			System.out.println("Executing statement...");
			ResultSet rs = preparedStatement.executeQuery();

			while (rs.next()) {
				int quantity = rs.getInt("quantity");
				if (quantity > 0) {
					System.out.println("Buying " + stockName);
				}
			}

		} catch (SQLException e) {
			throw new IllegalStateException(e);
		} finally {
			if (conn != null) {
				try {
					conn.close();
				} catch (SQLException e) {
					System.err.format("SQL State: %s\n%s", e.getSQLState(), e.getMessage());
				}
			}
		}
	}
}