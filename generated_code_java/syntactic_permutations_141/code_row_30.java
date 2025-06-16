import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class DatabaseConnection {
    public static Connection getConnection() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            return DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/employees?" +
                    "user=root&password=secret");
        } catch (Exception e) {
            throw new RuntimeException("Could not establish a database connection", e);
        }
    }
}