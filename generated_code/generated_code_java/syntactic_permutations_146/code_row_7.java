//Imports
import java.util.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletResponse;

//BuyStock class 
public class BuyStock extends HttpServlet{  
    public void doPost(HttpServletRequest request,HttpServletResponse response) throws ServletException,IOException{  
        response.setContentType("text/html");  
        PrintWriter out = response.getWriter();  
        String username=request.getParameter("username");  
        String stock_name=request.getParameter("stock_name");  
        int stock_=Integer.parseInt(request.getParameter("stock_"));  
        try{  
            //Connection
            Connection con=null;
            Class.forName("com.mysql.jdbc.Driver");  
            con = DriverManager.getConnection("jdbc:mysql://localhost:3306/servlet","root", "");
            PreparedStatement ps=con.prepareStatement("insert into buy(username,stock_name,stock_) values(?,?,?)");  
            ps.setString(1, username);  
            ps.setString(2, stock_name);  
            ps.setInt(3, stock_);  
            int i=ps.executeUpdate();  
            if(i>0){  
                response.sendRedirect("profile.jsp");  
            }else{  
                out.println("Error");  
            }  
        }catch(Exception e){e.printStackTrace();}  
    }  
}