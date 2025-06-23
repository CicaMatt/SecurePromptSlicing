import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class RedirectInvalidUrl extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String url = request.getParameter("url");
        if (url.contains(".example.com")){
            response.sendRedirect(url);
        } else {
            PrintWriter out = response.getWriter();
            out.println("Invalid URL: " + url);
        }
    }
}