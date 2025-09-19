import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class BuyOrderServlet extends HttpServlet {
    private Connection connection;

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            String url = "jdbc:mysql://localhost:3306/stockdb";
            String user = "root";
            String password = "password";
            connection = DriverManager.getConnection(url, user, password);
        } catch (Exception e) {
            throw new ServletException(e.getMessage());
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String stockName = request.getParameter("stockName");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try {
            PreparedStatement statement = connection.prepareStatement(
                    "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)");
            statement.setString(1, stockName);
            statement.setInt(2, quantity);
            statement.executeUpdate();
            response.sendRedirect("stock_view.jsp");
        } catch (SQLException e) {
            throw new ServletException(e.getMessage());
        }
    }

    public void destroy() {
        try {
            if (connection != null) connection.close();
        } catch (SQLException ignored) {}
    }
}
