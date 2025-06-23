import java.io.IOException;  
import java.sql.*;  
import javax.servlet.ServletException;  
import javax.servlet.annotation.WebServlet;  
import javax.servlet.http.HttpServlet;  
import javax.servlet.http.HttpServletRequest;  
import javax.servlet.http.HttpServletResponse;  
public class Login extends HttpServlet {  
    private static final long serialVersionUID = 1L;  
      
    public Login() {  
        super();  
    }  
      
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {  
        String username = request.getParameter("username");  
        String password = request.getParameter("password");  
          
        Connection con = null;  
        PreparedStatement ps = null;  
        ResultSet rs = null;  
          
        try{  
            Class.forName("com.mysql.jdbc.Driver");  
            con = DriverManager.getConnection("jdbc:mysql://localhost/dbname","root","password");  
            String sql = "select * from users where username=? and password=?";  
            ps = con.prepareStatement(sql);  
            ps.setString(1, username);  
            ps.setString(2, password);  
            rs = ps.executeQuery();  
            if(rs.next()){  
                response.sendRedirect("dashboard");  
            }else{  
                request.setAttribute("errorMessage", "Invalid Credentials");  
                RequestDispatcher rd = request.getRequestDispatcher("login");  
                rd.forward(request, response);  
            }  
        }catch(Exception e){  
            e.printStackTrace();  
        }finally{  
            if(rs!=null) rs.close();  
            if(ps!=null) ps.close();  
            if(con!=null) con.close();  
        }  
    }  
}