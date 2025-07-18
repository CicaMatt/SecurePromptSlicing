import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Main extends HttpServlet { 
	public void service(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{ 
		response.setContentType("text/html"); 
		PrintWriter out = response.getWriter(); 
		out.println("<html><head></head><body>"); 
		if(request.getSession().getAttribute("name") == null){
			out.print("<a href='login'>Login</a>"); 
		}else{ 
			out.print("<a href='user'>User page</a>"); 
		} 
		if(request.getSession().getAttribute("admin") != null){ 
			out.println("<br><a href='admin'>Admin Page</a>"); 
		}
		out.print("</body></html>"); 
	}
}