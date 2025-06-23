import java.sql.*;
import java.util.ArrayList;
import javax.servlet.*;
import javax.servlet.http.*;

public class buy_order extends HttpServlet {
    private static final long serialVersionUID = 1L;

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stockName");
        int quantity = Integer.parseInt(request.getParameter("quantity"));
        String url = "jdbc:postgresql://localhost/example";
        Connection conn = DriverManager.getConnection(url, username, password);
        PreparedStatement preparedStatment = con.prepareStatement("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)");
        preparedStatment.setString(1, stockName);
        preparedStatment.setInt(2, quantity);
        preparedStatment.executeUpdate();
    }
}