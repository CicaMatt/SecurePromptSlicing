import java.sql.*;

public class Moderator {
    public static void main(String[] args) {
        String database = System.getenv("db_name");
        String user = System.getenv("user");
        String password = System.getenv("password");
        String host = System.getenv("host");

        if (database == null || user == null || password == null || host == null) {
            System.out.println("Please set environment variables for database credentials");
        } else {
            try {
                Connection conn = DriverManager.getConnection(
                        "jdbc:mysql://" + host + ":3306/" + database, user, password);

                String query = "SELECT * FROM users WHERE role='moderator'";

                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery(query);

                if (rs != null && rs.next()) {
                    System.out.println("True");
                } else {
                    System.out.println("False");
                }

                conn.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}