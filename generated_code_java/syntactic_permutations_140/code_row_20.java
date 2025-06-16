import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class UserExist {
	private static final String DB_URL = "jdbc:sqlite::memory:";
	private Connection connection;
	private Statement statement;

	public UserExist() throws SQLException, ClassNotFoundException {
		Class.forName("org.sqlite.JDBC");
		connection = DriverManager.getConnection(DB_URL);
		statement = connection.createStatement();
	}

	private void createTable() throws SQLException {
		String sql = "CREATE TABLE IF NOT EXISTS USER (" + "ID INTEGER PRIMARY KEY," + "USERNAME TEXT NOT NULL UNIQUE,"
				+ "PASSWORD TEXT NOT NULL" + ")";
		statement.execute(sql);
	}

	public Boolean userExist(String username) throws SQLException {
		createTable();
		String sql = "SELECT * FROM USER WHERE USERNAME = ?";
		PreparedStatement preparedStatement = connection.prepareStatement(sql);
		preparedStatement.setString(1, username);
		ResultSet resultSet = preparedStatement.executeQuery();

		if (resultSet.next()) {
			return true;
		}

		return false;
	}

	public static void main(String[] args) throws SQLException, ClassNotFoundException {
		UserExist userExist = new UserExist();
		System.out.println(userExist.userExist("user1"));
	}
}