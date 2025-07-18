import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;

    public class RedirectInvalidURL extends HttpServlet {
        public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
            String url = req.getParameter("url");
            if (url.startsWith("https://example.com")) {
                res.sendRedirect(url);
            } else {
                res.setContentType("text/plain");
                PrintWriter out = res.getWriter();
                out.println("Invalid URL.");
            }
        }
    }