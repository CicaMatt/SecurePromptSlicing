import java.sql.*;

public class DatabaseConnection {
    public static void main(String[] args) throws SQLException {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/world?useSSL=false", "root", "password");
                Statement statement = conn.createStatement();
                ResultSet resultSet = statement.executeQuery("SELECT * FROM countries WHERE continent = 'Asia'")) {
            System.out.println(resultSet);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}