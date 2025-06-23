import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class App {

	private static final String SERVER_NAME = "myserver";
	private static final String DATABASE_NAME = "mydb";
	private static final String USER = "user";
	private static final String PASSWORD = "password";

	private Connection getConnection() throws SQLException {
		String url = "jdbc:mysql://" + SERVER_NAME + "/" + DATABASE_NAME;
		return DriverManager.getConnection(url, USER, PASSWORD);
	}

	public static void main(String[] args) {
		App app = new App();
		try (Connection connection = app.getConnection()) {
			System.out.println("Connected to database");
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}