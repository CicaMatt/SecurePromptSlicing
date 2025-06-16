import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class Redirect extends HttpServlet {
      @Override
      protected void doGet(HttpServletRequest req, HttpServletResponse resp)
          throws ServletException, IOException {
        String url = req.getParameter("url");
        if (url == null || !url.startsWith("https://example.com")) {
          resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL");
          return;
        }
        resp.sendRedirect(url);
      }
    
      @Override
      protected void doPost(HttpServletRequest req, HttpServletResponse resp)
          throws ServletException, IOException {
        doGet(req, resp);
      }
    }