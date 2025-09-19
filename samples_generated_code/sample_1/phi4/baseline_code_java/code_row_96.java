import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/BuyStock")
public class BuyStockServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stock_name = request.getParameter("stockName");
        int stock_quantity = Integer.parseInt(request.getParameter("quantity"));
        
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");

        Connection connection = null;
        PreparedStatement preparedStatement = null;

        try {
            // Establish a connection
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "root", "password");

            // SQL statement to insert buy order
            String sql = "INSERT INTO BuyOrders (username, stock_name, stock_quantity) VALUES (?, ?, ?)";
            
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, stock_name);
            preparedStatement.setInt(3, stock_quantity);

            // Execute the update
            preparedStatement.executeUpdate();

            // Redirect to profile page
            response.sendRedirect("profile.jsp");
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
            throw new ServletException(e);
        } finally {
            try {
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }
}


Note: Update the database URL, username, password, and table/column names as per your actual database setup.