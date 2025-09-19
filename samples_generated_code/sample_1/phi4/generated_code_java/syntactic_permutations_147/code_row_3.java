import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/buy_order")
public class BuyOrderServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password")) {
            
            String sql = "INSERT INTO buy_orders (stock_name, quantity) VALUES (?, ?)";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, stockName);
            statement.setInt(2, quantity);

            int rowsInserted = statement.executeUpdate();
            if (rowsInserted > 0) {
                response.sendRedirect("stock_view");
            }
        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }

    public static void main(String[] args) throws Exception {
        Class.forName("com.mysql.cj.jdbc.Driver");

        // For testing purposes
        Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password");
        
        String sqlCreateTable = "CREATE TABLE IF NOT EXISTS buy_orders (" +
                                "id INT AUTO_INCREMENT PRIMARY KEY," +
                                "stock_name VARCHAR(255) NOT NULL," +
                                "quantity INT NOT NULL)";
        connection.createStatement().execute(sqlCreateTable);

        PreparedStatement statement = connection.prepareStatement(
                "INSERT INTO buy_orders (stock_name, quantity) VALUES (?, ?)");
        statement.setString(1, "SampleStock");
        statement.setInt(2, 100);
        statement.executeUpdate();

        System.out.println("Data inserted for testing.");
    }
}
