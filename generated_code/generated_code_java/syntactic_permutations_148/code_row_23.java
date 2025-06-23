import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
import java.sql.*;
public class Post extends HttpServlet{
    public void doPost(HttpServletRequest request,HttpServletResponse response) throws ServletException,IOException{
        String user_name=request.getParameter("username");
        String message=request.getParameter("message");
        insert_user_message_in_db(user_name,message);
        RequestDispatcher rd=request.getRequestDispatcher("/main.jsp");
        rd.forward(request,response);
    }
    public void insert_user_message_in_db(String user_name,String message){
        Connection con=null;
        PreparedStatement ps=null;
        try{
            Class.forName("com.mysql.jdbc.Driver");
            con=DriverManager.getConnection("jdbc:mysql://localhost:3306/chatroom","root","");
            ps=con.prepareStatement("insert into message(user_name,message) values(?,?)");
            ps.setString(1,user_name);
            ps.setString(2,message);
            ps.executeUpdate();
        }catch(Exception e){
            System.out.println(e);
        }
    }
}