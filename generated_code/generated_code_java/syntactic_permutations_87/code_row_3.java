import java.sql.*;

public class Temperature_for_location {
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        String connectionURL = "jdbc:mysql://localhost/world";
        Connection con = null;
        Statement statement = null;
        ResultSet rs = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            con = DriverManager.getConnection(connectionURL, "root", "admin");
            if (con != null) {
                System.out.println("Connected to database.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}