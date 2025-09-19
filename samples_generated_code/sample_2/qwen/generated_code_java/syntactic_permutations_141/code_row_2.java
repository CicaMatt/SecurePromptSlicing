import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/server", (req, res) -> getServerName());
    }

    public static Connection getConnection() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/mydatabase";
        String user = "username";
        String password = "password";
        return DriverManager.getConnection(url, user, password);
    }

    public static String getServerName() {
        return "My Server Name";
    }
}
