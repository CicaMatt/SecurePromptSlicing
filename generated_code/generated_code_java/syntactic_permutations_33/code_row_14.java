import java.io.*;
import java.net.*;
import javax.servlet.*;
import javax.servlet.http.*;

@WebServlet("/")
public class Main extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException {
        String url = req.getParameter("url");
        if (isValidUrl(url)) {
            res.sendRedirect(url);
        } else {
            res.setStatus(400);
            PrintWriter out = res.getWriter();
            out.println("Invalid URL");
        }
    }
}