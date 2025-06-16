import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class UnsubscribeServlet extends HttpServlet{
    
    private static final String dbUrl = "jdbc:mysql://localhost/newsletter";
    private static final String dbUser="root";
    private static final String dbPassword ="password";

    protected void doGet(HttpServletRequest request,HttpServletResponse response) throws ServletException,IOException{
        Connection conn =null;
        Statement stmt = null;
        ResultSet rs = null;
        
        String email=request.getParameter("email");
        if(!isSubscribed(conn,email)){
            response.setContentType("text/plain");
            response.getWriter().println("You are not subscribed");
            return;
        }
        else{
            deleteUser(conn,stmt,rs,email);
            unsubscribeFromMailingList(email);
            
            response.setContentType("text/plain");
            response.getWriter().println("You have successfully been unsubscribed from our newsletter.");
        }
    }
    
    private boolean isSubscribed(Connection conn,String email){
        try{
            Class.forName("com.mysql.jdbc.Driver");
            conn= DriverManager.getConnection(dbUrl,dbUser,dbPassword);
            
            String sql="SELECT * FROM subscribers WHERE email = ?";
            PreparedStatement ps = conn.prepareStatement(sql);
            ps.setString(1,email);
            ResultSet rs = ps.executeQuery();
            
            if(rs.next()){
                return true;
            }
        }catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        }finally{
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        
        return false;
    }
    
    private void deleteUser(Connection conn,Statement stmt,ResultSet rs,String email){
        try{
            String sql="DELETE FROM subscribers WHERE email= ?";
            PreparedStatement ps = conn.prepareStatement(sql);
            ps.setString(1,email);
            ps.executeUpdate();
            
            
        } catch (SQLException e) {
            e.printStackTrace();
        }finally{
            try {
                stmt.close();
                rs.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
    
    private void unsubscribeFromMailingList(String email){
        //code to unsubscribe from mailing list goes here
    }
}