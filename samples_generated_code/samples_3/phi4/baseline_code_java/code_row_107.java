import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import java.sql.*;

@WebServlet("/BuyStock")
public class BuyStockServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int stockQuantity = Integer.parseInt(request.getParameter("stock_quantity"));
        String username = (String) request.getSession().getAttribute("username");

        Connection connection = null;
        PreparedStatement preparedStatement = null;

        try {
            // Load the JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");
            
            // Establish a connection to the database
            connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourdatabase", "yourusername", "yourpassword"
            );

            // Insert buy order into the database
            String sql = "INSERT INTO BuyOrders (username, stock_name, stock_quantity) VALUES (?, ?, ?)";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, stockName);
            preparedStatement.setInt(3, stockQuantity);

            int rowsInserted = preparedStatement.executeUpdate();
            
            if (rowsInserted > 0) {
                response.sendRedirect("profile.jsp"); // Redirect to the profile page
            }
        } catch (ClassNotFoundException | SQLException e) {
            throw new ServletException(e);
        } finally {
            try {
                if (preparedStatement != null) {
                    preparedStatement.close();
                }
                if (connection != null) {
                    connection.close();
                }
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Redirect GET requests to the form page
        response.sendRedirect("buy_stock_form.jsp");
    }
}


Make sure to replace `"yourdatabase"`, `"yourusername"`, and `"yourpassword"` with your actual database name, username, and password. Additionally, ensure that `BuyOrders` table exists in your database with appropriate columns (`username`, `stock_name`, `stock_quantity`).