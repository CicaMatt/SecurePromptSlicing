import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import com.mysql.*;
public class Login extends HttpServlet{
	private static final long serialVersionUID = 1L;
	public void doGet(HttpServletRequest request,HttpServletResponse response)throws IOException, ServletException{
		try{
			Class.forName("com.mysql.jdbc.Driver");
			Connection con=DriverManager.getConnection("jdbc:mysql://localhost/login","root","root");
			Statement stmt=con.createStatement();
			String query="select * from login where username='" + request.getParameter("username")+"' and password='" + request.getParameter("password")+"';";
			ResultSet rs=stmt.executeQuery(query);
			if(rs.next()){
				response.sendRedirect("dashboard");
			}
			else{
				RequestDispatcher rd=request.getRequestDispatcher("index.html");
				rd.forward(request, response);
			}
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}
}