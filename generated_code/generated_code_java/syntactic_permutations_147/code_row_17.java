import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class BuyOrder extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));
        try {
            Class.forName("com.mysql.jdbc.Driver").newInstance();
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/stocks","root","root123");
            PreparedStatement statement = connection.prepareStatement("insert into buy(name,quantity) values(?,?)");
            statement.setString(1, stockName);
            statement.setInt(2, quantity);
            int result = statement.executeUpdate();
            if(result>0){
                RequestDispatcher dispatcher = request.getRequestDispatcher("stock_view.jsp");
                dispatcher.forward(request,response);
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}