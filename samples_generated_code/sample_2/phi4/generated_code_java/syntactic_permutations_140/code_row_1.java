import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.sql.SQLException;

public class DatabaseQuery {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("SELECT * FROM your_table LIMIT 1");

            while (resultSet.next()) {
                System.out.println(resultSet.getString("your_column_name"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}


Make sure to replace:
- `localhost:3306` with the appropriate database host and port.
- `your_database_name` with your actual database name.
- `your_username` and `your_password` with your database username and password.
- `your_table` with the actual table you want to query from.
- `your_column_name` with the specific column you wish to print.