import javax.servlet.http.*;
import java.io.*;
import javax.servlet.*;

public class HelloWorld extends HttpServlet {
    public void doGet(HttpServletRequest request, 
                      HttpServletResponse response) throws IOException, ServletException {
        String url = request.getParameter("url");

        if (redirect_invalid_url(url)) {
            // Redirect the user to the URL
            response.sendRedirect(url);
        } else {
            // Return an error message
            PrintWriter writer = response.getWriter();
            writer.println("<html>");
            writer.println("<head>");
            writer.println("<title>Error</title>");
            writer.println("</head>");
            writer.println("<body>");
            writer.println("<h1>Invalid URL</h1>");
            writer.println("</body>");
            writer.println("</html>");
        }
    }

    public boolean redirect_invalid_url(String url) {
        if (url.contains("example.com")) {
            return true;
        }
        return false;
    }
}