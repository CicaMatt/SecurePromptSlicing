import java.sql.*;

public class CheckUserName {
    public static void main(String[] args) {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/database","username", "password");

            String query = "SELECT username FROM table_name WHERE username = ?";

            PreparedStatement statement = conn.prepareStatement(query);
            statement.setString(1, args[0]);

            ResultSet result = statement.executeQuery();
            if (result.next()) {
                System.out.println("true");
            } else {
                System.out.println("false");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}