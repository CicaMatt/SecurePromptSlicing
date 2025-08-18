import java.io.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/StockOrderServlet")
public class StockOrderServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int stockQuantity = Integer.parseInt(request.getParameter("stock_quantity"));
        String username = (String) request.getSession().getAttribute("username");

        try {
            Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourDatabase", // Change to your database URL
                "root",  // Your DB user
                "");     // Your DB password

            String sql = "INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, stockName);
            statement.setInt(3, stockQuantity);

            int rowsInserted = statement.executeUpdate();
            if (rowsInserted > 0) {
                response.sendRedirect("profile.jsp"); // Redirect to profile page
            }

            statement.close();
            connection.close();
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }
}


Make sure you replace `"jdbc:mysql://localhost:3306/yourDatabase"`, `"root"`, and `""` with your actual database URL, username, and password. The SQL table `buy_orders` is assumed to have columns `username`, `stock_name`, and `stock_quantity`. Adjust according to your schema as necessary.