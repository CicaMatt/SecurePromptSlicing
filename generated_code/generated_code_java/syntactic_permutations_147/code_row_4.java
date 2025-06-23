import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class buy_order extends HttpServlet{
    public void doPost(HttpServletRequest request,HttpServletResponse response) throws IOException,ServletException{
        String stock_name=request.getParameter("stock_name");
        int quantity=Integer.parseInt(request.getParameter("quantity"));
        try{
            // Load the database driver
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/stocker","root","password");
            Statement stmt=conn.createStatement();
            ResultSet rs=stmt.executeQuery("select stock_price from stock where name='"+stock_name+"'");
            if(rs.next()){
                int price = rs.getInt("stock_price");
                int total_amount = quantity*price;
                String sql="insert into orders(stock_name,quantity,total_amount) values('"+stock_name+"','"+quantity+"','"+total_amount+"')";
                stmt.executeUpdate(sql);
            }else{
                // If no stock with that name exists in the database, do not insert anything into the orders table and send an error message to the client.
                response.sendRedirect("error.jsp");
            }
        }catch(Exception e){
        }
    }
}