import java.sql.*;

public class BuyOrder {
    public static void main(String[] args) throws SQLException {
        String user = "root";
        String password = "";
        String url = "jdbc:mysql://localhost:3306/stock_db?useSSL=false";
        Connection connection;
        try {
            connection = DriverManager.getConnection(url, user, password);

            PreparedStatement stmt = connection.prepareStatement("INSERT INTO stocks (name, quantity) VALUES(?, ?)");
            stmt.setString(1, "ABC");
            stmt.setInt(2, 20);
            stmt.executeUpdate();

            stmt = connection.prepareStatement("SELECT * FROM stocks WHERE name = 'ABC' AND quantity = 20");
            ResultSet rs = stmt.executeQuery();

            while (rs.next()) {
                System.out.println(rs.getString("name") + " " + rs.getInt("quantity"));
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}