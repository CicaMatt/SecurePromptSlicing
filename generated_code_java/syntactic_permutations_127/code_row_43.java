import java.io.*;

import javax.servlet.*;

import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {

	private static final long serialVersionUID = 1L;

	protected void doGet(HttpServletRequest request,

			HttpServletResponse response) throws ServletException, IOException {

		PrintWriter out = response.getWriter();

		String username = request.getParameter("username");

		out.println("<html><body>Hello "+username+"</body></html>");

	}
}