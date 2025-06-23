import java.io.IOException; 
import javax.servlet.http.*;
import org.json.*;  
import java.util.Map; 
import java.sql.*;

public class LoginHandler extends HttpServlet {
    protected void do_login(HttpServletRequest request, HttpServletResponse response) throws IOException { 
        String username = request.getParameter("username"); 
        String password = request.getParameter("password");  
        JSONObject json = new JSONObject(); 
        try {
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/database?useSSL=false", "root", "password");
            PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username=? AND password=?;"); 
            stmt.setString(1, username); 
            stmt.setString(2, password);  
            ResultSet res = stmt.executeQuery();  
            if (res.next()) { 
                json.put("status", "success");   
            } else { 
                json.put("status", "failure");    
            }
        } catch(Exception e) {  
            json.put("status", "exception");  
        }
        response.getWriter().print(json);
    }
    protected void user_page(HttpServletRequest request, HttpServletResponse response) throws IOException { 
        String username = request.getParameter("username"); 
        JSONObject json = new JSONObject(); 
        try {
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/database?useSSL=false", "root", "password");
            PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username=?;");
            stmt.setString(1, username); 
            ResultSet res = stmt.executeQuery();  
            if (res.next()) { 
                json.put("status", "success");   
                json.put("username", username);  
                json.put("email", res.getString("email"));  
                json.put("phone", res.getString("phone"));  
                json.put("city", res.getString("city")); 
            } else { 
                json.put("status", "failure");   
            }
        } catch(Exception e) {  
            json.put("status", "exception");  
        }
        response.getWriter().print(json);
    }
    protected void admin_page(HttpServletRequest request, HttpServletResponse response) throws IOException { 
        JSONObject json = new JSONObject(); 
        try {
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/database?useSSL=false", "root", "password");
            PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users;");
            ResultSet res = stmt.executeQuery(); 
            while (res.next()) {  
                json.put(res.getString("username"), new JSONObject().put("email", res.getString("email")).put("phone", res.getString("phone")));
            }
        } catch(Exception e) {  
            json.put("status", "exception");  
        }
        response.getWriter().print(json);
    }
}