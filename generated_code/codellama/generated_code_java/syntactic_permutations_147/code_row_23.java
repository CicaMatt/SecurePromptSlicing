import java.sql.*;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.annotation.WebServlet;
@WebServlet("/buy_order")
public class BuyOrder extends HttpServlet {
    private static final String url = "jdbc:sqlite:/path/to/db";
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException{
        String name = request.getParameter("stockName");
        int quantity = Integer.parseInt(request.getParameter("quantity"));
        try{
            Connection connection = DriverManager.getConnection(url);
            Statement statement = connection.createStatement();
            statement.executeUpdate(String.format("INSERT INTO stocks (name, quantity) VALUES ('%s', %d)", name, quantity));
        }catch(SQLException e){
            System.out.println("Error: " + e);
        }
        response.sendRedirect("/stock_view");
    }
}