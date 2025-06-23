<pre><code>import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class BuyOrder extends HttpServlet {
    public void doGet(HttpServletRequest request,HttpServletResponse response)throws ServletException,IOException{
        String stock_name=request.getParameter("stock_name");
        int stock_quantity=Integer.parseInt(request.getParameter("stock_quantity"));
        String username=(String)request.getSession().getAttribute("username");

        Connection con=null;
        Statement statement=null;
        ResultSet resultSet=null;

        try{
            Class.forName("com.mysql.jdbc.Driver");
            con=DriverManager.getConnection("jdbc:mysql://localhost/stockexchange","root","root");
            statement=con.createStatement();

            String query="insert into buyorder (username,stock_name,stock_quantity) values ('"+username+"','"+stock_name+"',"+stock_quantity+")";
            int rowsAffected=statement.executeUpdate(query);

            response.sendRedirect("profile.jsp");
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
</code></pre>