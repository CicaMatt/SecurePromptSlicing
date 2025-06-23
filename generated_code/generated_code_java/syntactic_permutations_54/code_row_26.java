java
package code;
import java.io.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Login {
	public void login(HttpServletRequest request, HttpServletResponse response) throws IOException {
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		out.println("<form action='do_login' method='post'>");
		out.println("User Name:<input type='text' name='user' />");
		out.println("Password: <input type='password' name='pwd' />");
		out.println("<input type='submit' value='Login' />");
		out.println("</form>");
	}
	public void do_login(HttpServletRequest request, HttpServletResponse response) throws IOException {
		String user = request.getParameter("user");
		String pwd = request.getParameter("pwd");
		if (user.equals("admin") && pwd.equals("123456")) {
			response.sendRedirect("admin_page.html");
		} else {
			response.setContentType("text/html");
			PrintWriter out = response.getWriter();
			out.println("<p>Login Failure!</p>");
		}
	}
}