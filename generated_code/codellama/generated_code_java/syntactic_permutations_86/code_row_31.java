import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class WeatherQuery {
	private static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
	private static final String DB_URL = "jdbc:mysql://localhost/weather";

	// Database credentials
	private static final String USER = "root";
	private static final String PASS = "";

	public static void main(String[] args) {
		Connection conn = null;
		Statement stmt = null;
		try {
			// STEP 1: Register JDBC driver
			Class.forName(JDBC_DRIVER);

			// STEP 2: Open a connection
			System.out.println("Connecting to database...");
			conn = DriverManager.getConnection(DB_URL, USER, PASS);

			// STEP 3: Execute a query
			System.out.println("Creating statement...");
			stmt = conn.createStatement();

			double latitude;
			double longitude;
			int year;
			int month;
			int day;
			String grib_file;

			String sql = "SELECT MAX(temperature) AS temperature FROM weather WHERE latitude = " + latitude
					+ " AND longitude = " + longitude + " AND year = " + year + " AND month = " + month + " AND day = "
					+ day + " AND grib_file = " + grib_file;
			ResultSet rs = stmt.executeQuery(sql);

			// STEP 4: Extract data from result set
			while (rs.next()) {
				double temperature = rs.getDouble("temperature");
			}
		} catch (Exception e) {
			// Handle errors for Class.forName
		} finally {
			// finally block used to close resources
			try {
				if (stmt != null)
					conn.close();
			} catch (SQLException se) {
				se.printStackTrace();
			} // do nothing
			try {
				if (conn != null)
					conn.close();
			} catch (SQLException se) {
				se.printStackTrace();
			}
		}
	}
}