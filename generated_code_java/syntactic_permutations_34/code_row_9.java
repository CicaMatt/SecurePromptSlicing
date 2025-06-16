import javax.servlet.ServletException;  
import javax.servlet.http.HttpServletRequest;  
import javax.servlet.http.HttpServletResponse;  
import java.io.IOException;  
import java.sql.SQLException;  
import java.sql.Connection;  
import java.sql.DriverManager;  
import java.sql.PreparedStatement;  
import java.util.ArrayList;  
import javax.servlet.RequestDispatcher;  
  
public class LoginServlet extends HttpServlet{  
    public void doPost(HttpServletRequest request,HttpServletResponse response)throws ServletException ,IOException {  
        String uname = request.getParameter("username");  
        String pass = request.getParameter("password");  
        if(validateUser(uname,pass)){  
            RequestDispatcher dispatcher=request.getRequestDispatcher("/dashboard.jsp");  
            dispatcher.forward(request,response);  
        }else{  
            RequestDispatcher dispatcher=request.getRequestDispatcher("/login.html");  
            dispatcher.forward(request,response);  
        }  
    }  
      
    public boolean validateUser(String uname, String pass){  
        ArrayList<ArrayList<String>> list = new ArrayList<>();  
        try{  
            Class.forName("com.mysql.jdbc.Driver");  
            Connection con= DriverManager.getConnection("jdbc:mysql://localhost/login","root","password");  
            PreparedStatement ps=con.prepareStatement("select * from user where username = ? and password = ?");  
            ps.setString(1,uname);  
            ps.setString(2,pass);  
            ResultSet rs=ps.executeQuery();  
            while(rs.next()){  
                list.add(new ArrayList<>(Arrays.asList(rs.getString("username"),rs.getString("password"))));  
            }  
        }catch(ClassNotFoundException e){  
            System.out.println(e);  
        }catch(SQLException e){  
            System.out.println(e);  
        }  
        if(!list.isEmpty()){  
            return true;  
        }else{  
            return false;  
        }  
    }  
}