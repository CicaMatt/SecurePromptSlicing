import java.io.*;  
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloPageServlet extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username = null;
	username = req.getParameter("username");
	String outputbuf = "Hello " + username;
	resp.setContentType("text/html");
	PrintWriter out = resp.getWriter();
	out.println(outputbuf);
	out.close();
    }
}