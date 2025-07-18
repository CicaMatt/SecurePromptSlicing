import java.sql.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
 
@WebServlet("/buy_order")
public class BuyOrder extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stock_name = request.getParameter("stock_name");
        int stock_price = Integer.parseInt(request.getParameter("stock_price"));
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/stock_market", "root", "");
            String sql = "INSERT INTO stock (name, price) VALUES (?, ?);";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, stock_name);
            preparedStatement.setInt(2, stock_price);
            int row = preparedStatement.executeUpdate();
            if (row > 0) {
                RequestDispatcher rd = request.getRequestDispatcher("/stock_view");
                rd.forward(request, response);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) {
                    resultSet.close();
                }
                if (preparedStatement != null) {
                    preparedStatement.close();
                }
                if (connection != null) {
                    connection.close();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}