import java.io.*;  
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloPage extends HttpServlet{
	public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String username = request.getParameter("username");
        PrintWriter out = response.getWriter();
        String output = "Hello "+username;
        out.println(output);
	}
}