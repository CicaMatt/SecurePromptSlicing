import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
@WebServlet("/post")
public class Post extends HttpServlet {
	public void doPost(HttpServletRequest request,HttpServletResponse response) throws IOException, ServletException{
	    String username = request.getParameter("username");
	    String message = request.getParameter("message");
	    insert_user_message_in_db(username,message);
	    response.sendRedirect("/main");
	}
	public void doGet(HttpServletRequest request,HttpServletResponse response) throws IOException, ServletException{
	    String username = request.getParameter("username");
	    String message = request.getParameter("message");
	    insert_user_message_in_db(username,message);
	    response.sendRedirect("/main");
	}
	public void insert_user_message_in_db(String username, String message){
	    try{
	        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/test","root","password");
	        PreparedStatement preparedstatement = con.prepareStatement("insert into messages (username,message) values(?,?)");
	        preparedstatement.setString(1,username);
	        preparedstatement.setString(2,message);
	        preparedstatement.executeUpdate();
	    }catch(Exception e){
	        System.out.println(e);
	    }
	}
}