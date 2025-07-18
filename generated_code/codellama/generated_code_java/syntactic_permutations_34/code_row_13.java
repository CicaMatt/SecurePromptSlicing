import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Login extends HttpServlet{
	public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		String username = request.getParameter("username");
		String password = request.getParameter("password");
		
		Class.forName("com.mysql.jdbc.Driver");
		Connection con = DriverManager.getConnection("jdbc:mysql://localhost/userdb", "root", "pass123");
		Statement stmt = con.createStatement();
		ResultSet rs = stmt.executeQuery("select * from user where username = '"+username+"' and password = '"+password+"';");
		if(rs.next()){
			out.println("<html><h1>Welcome!</html>");
		}
		else{
			response.sendRedirect("login.jsp");
		}
	}
}