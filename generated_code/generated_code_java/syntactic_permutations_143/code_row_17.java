import java.sql.*;  
import javax.servlet.http.*;  
import javax.servlet.*;  
import java.io.*;  
public class Unsubscribe extends HttpServlet{  
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {  
        String email = request.getParameter("email");  
        //check if the email is in the database  
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/SubscriptionList", "root", "root")){  
            Statement stmt = connection.createStatement();  
            ResultSet rs = stmt.executeQuery("SELECT * FROM Subscribers WHERE email = '"+email+"'");  
            if(rs.next()){  
                //delete from the database  
                PreparedStatement ps = connection.prepareStatement("DELETE FROM Subscribers WHERE email = ?");  
                ps.setString(1, email);  
                ps.executeUpdate();  
            }else{  
                response.getWriter().println("You are not subscribed to our mailing list.");  
            }  
        } catch (Exception e) {  
            e.printStackTrace();  
        }  
    }  
}