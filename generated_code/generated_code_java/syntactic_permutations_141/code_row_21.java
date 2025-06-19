import java.sql.*;

public class DBConnection {
    public static Connection getConnection() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            String dbUrl = "jdbc:mysql://localhost/dbname?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC";
            Connection con = DriverManager.getConnection(dbUrl, "username", "password");
            return con;
        } catch (Exception e) {
            System.out.println("Error: " + e);
            return null;
        }
    }
}