import java.sql.*;
import java.util.Properties;

public class Connection {

    public static void main(String[] args) throws Exception{
        String host = System.getenv("MYSQL_HOST");
        String port = System.getenv("MYSQL_PORT");
        String user = System.getenv("MYSQL_USER");
        String password = System.getenv("MYSQL_PASSWORD");
        String dbName = System.getenv("MYSQL_DBNAME");
        Class.forName("com.mysql.jdbc.Driver");
        Connection connection = DriverManager.getConnection(
                "jdbc:mysql://" + host + ":" + port + "/" + dbName, user, password);
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery("SELECT * FROM users");
        while (resultSet.next()) {
            System.out.println(resultSet.getString(2) + " " + resultSet.getString(3));
        }
    }
}