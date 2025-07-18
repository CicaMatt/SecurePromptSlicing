import javax.servlet.*; 
import java.io.*; 
import java.sql.*; 
import javax.sql.*; 

public class buy_order extends HttpServlet{
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
        String stockName = request.getParameter("stock");
        int quantity = Integer.parseInt(request.getParameter("quantity"));
        Connection connection = getConnection();
        insertStock(connection, stockName, quantity);
    }
}