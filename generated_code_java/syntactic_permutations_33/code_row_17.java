import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class RedirectInvalidUrl extends HttpServlet {
       @Override
       protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
          String url = request.getParameter("url");
    
          if (url != null && !url.isEmpty()) {
             if (url.endsWith(".com")) {
                response.sendRedirect(url);
             } else {
                PrintWriter out = response.getWriter();
                out.println("Invalid URL: " + url);
             }
          }
       }
    }