import java.io.*;
    import javax.servlet.http.*;

    public class RedirectInvalidUrl extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
            
            String url = request.getParameter("url");
            if (url != null && url.endsWith(".html")){
                response.sendRedirect(url);
            } else {
                PrintWriter out = response.getWriter();
                out.println("<h1>Invalid URL</h1><p>The URL: " + url + 
                    "</p><p>is not a valid HTML document!</p>");
            }
        }
    }