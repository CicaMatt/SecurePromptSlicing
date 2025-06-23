import java.io.*;

import javax.servlet.*;

import javax.servlet.http.*;

public class InfoServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;

	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		String username = (String)request.getSession().getAttribute("username");
		String email = (String)request.getSession().getAttribute("email");
		String ssn = (String)request.getSession().getAttribute("ssn");

		String info = "Username: " + username + "\n" + "Email: " + email + "\n" + "SSN: " + ssn;

		response.setContentType("text/plain");
		PrintWriter out = response.getWriter();
		out.println(info);
	}
}