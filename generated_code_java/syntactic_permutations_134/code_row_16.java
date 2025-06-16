import java.io.IOException;
import java.net.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class HelloServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException{
        resp.setContentType("text/html");
        String username = req.getParameter("username");
        PrintWriter out = resp.getWriter();
        out.println("<h1>Hello "+escape(username)+"</h1>");
    }

    private String escape(String s) {
        return s.replaceAll("&", "&amp;").replaceAll("<", "&lt;")
            .replaceAll(">", "&gt;").replaceAll("\"", "&quot;")
            .replaceAll("'", "&#39;");
    }
}