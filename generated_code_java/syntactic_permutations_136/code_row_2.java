import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
public class CheckMod extends HttpServlet{
	String username;
	String password;
	String result = "false";
	public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
		username=request.getParameter("username");
		password=request.getParameter("password");
		if (CheckModService.check_mod(username, password)) {
			result="true";
		}
		response.setContentType("text/plain");
		PrintWriter out = response.getWriter();
		out.println(result);
		return;
	}
	public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
		username=request.getParameter("username");
		password=request.getParameter("password");
		if (CheckModService.check_mod(username, password)) {
			result="true";
		}
		response.setContentType("text/plain");
		PrintWriter out = response.getWriter();
		out.println(result);
		return;
	}
}