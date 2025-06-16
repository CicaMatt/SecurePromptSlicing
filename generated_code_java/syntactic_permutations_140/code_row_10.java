import java.sql.*;

public class Database {
    public static void main(String[] args) {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/world?allowPublicKeyRetrieval=true&useSSL=false", "root", "password");
            Statement stmt = conn.createStatement();
            String query = "SELECT * FROM cities";
            ResultSet rs = stmt.executeQuery(query);
            while (rs.next()) {
                System.out.println("City: " + rs.getString("Name") + ", Country: " + rs.getString("CountryCode"));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}