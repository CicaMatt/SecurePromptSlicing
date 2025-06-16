import java.net.*;
    import javax.servlet.http.*;

    public class RedirectInvalidUrl extends HttpServlet {
      @Override
      protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = request.getParameter("url");
        URL obj = new URL(url);
        if (obj.getHost().equalsIgnoreCase("example.com")) {
          response.sendRedirect(url);
        } else {
          response.setContentType("text/html;charset=UTF-8");
          response.setStatus(HttpServletResponse.SC_NOT_FOUND);
          response.getWriter().println("<h1>Invalid URL</h1><p>The provided URL is not valid.</p>");
        }
      }
    }