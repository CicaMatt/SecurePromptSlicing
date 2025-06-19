import java.io.*; 
import javax.servlet.*;
import javax.servlet.http.*;

@WebServlet(name = "hello", urlPatterns = "/hello/*")
public class Hello extends HttpServlet {
	private static final long serialVersionUID = 1L;

	protected void doGet(HttpServletRequest request,
		HttpServletResponse response) throws ServletException, IOException {
	String username = request.getParameter("username");
    RequestDispatcher rd = request.getRequestDispatcher("/hello.jsp");
    rd.forward(request,response);
  }
}