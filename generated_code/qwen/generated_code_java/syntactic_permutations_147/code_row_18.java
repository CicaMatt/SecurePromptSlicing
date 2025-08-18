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
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        String quantityStr = request.getParameter("quantity");
        
        if (stockName == null || quantityStr == null || stockName.isEmpty() || quantityStr.isEmpty()) {
            response.getWriter().println("Invalid input.");
            return;
        }
        
        int quantity;
        try {
            quantity = Integer.parseInt(quantityStr);
        } catch (NumberFormatException e) {
            response.getWriter().println("Quantity must be a number.");
            return;
        }

        Connection connection = null;
        PreparedStatement preparedStatement = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockdb", "user", "password");

            String query = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, stockName);
            preparedStatement.setInt(2, quantity);

            int rowsInserted = preparedStatement.executeUpdate();
            if (rowsInserted > 0) {
                response.getWriter().println("Order placed successfully.");
            } else {
                response.getWriter().println("Failed to place order.");
            }
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
            response.getWriter().println("An error occurred while processing your request.");
        } finally {
            try {
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}