import java.sql.*;
public class Main {
    public static void main(String[] args) throws Exception {
        String dbUrl = "jdbc:sqlite:test.db";
        Connection conn = DriverManager.getConnection(dbUrl);
        if (conn != null) {
            DatabaseMetaData meta = conn.getMetaData();
            System.out.println("The driver name is " + meta.getDriverName());
            System.out.println("A new database has been created.");
        }
    }
}