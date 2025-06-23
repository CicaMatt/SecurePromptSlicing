import java.sql.*;

public class Main {
    public static void main(String[] args) {
        Connection connection = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost/stock_database",
                    "root", "password");

            String stock_name = request.getParameter("stock_name");
            int quantity = Integer.parseInt(request.getParameter("quantity"));

            PreparedStatement statement = connection.prepareStatement("insert into buy (stock_name, quantity) values(?, ?)");
            statement.setString(1, stock_name);
            statement.setInt(2, quantity);
            statement.executeUpdate();
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}