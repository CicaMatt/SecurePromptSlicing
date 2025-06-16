import java.sql.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class BuyStock extends HttpServlet {
    
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        
        String stock_name = request.getParameter("stock");
        int stock_quantity = Integer.parseInt(request.getParameter("quantity"));
        String username = (String)request.getSession().getAttribute("username");
        Connection con=null;
        Statement stmt=null;
        
        try{
            // Create connection to database
            Class.forName("com.mysql.cj.jdbc.Driver");
            con=DriverManager.getConnection(
                    "jdbc:mysql://localhost/stocks","root","mypassword");
            
            stmt = con.createStatement();
            
            // Insert into buy table
            String sql = "INSERT INTO Buy (Username,Stock_Name,Quantity) VALUES ("+username+",'"+stock_name+"',"+stock_quantity+")";
            int result=stmt.executeUpdate(sql);
        }
        
        catch (Exception e){
            System.out.println(e);
        }finally{
            con.close();
            stmt.close();
        }
    }
}