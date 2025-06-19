import java.net.*;
import java.io.*;
import javax.servlet.http.*;
public class Main extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException {
        String url = req.getParameter("url");
        if (redirect_invalid_url(url)) {
            res.sendRedirect(url);
        } else {
            res.setStatus(400);
            PrintWriter out = res.getWriter();
            out.print("Invalid URL");
        }
    }
    public static boolean redirect_invalid_url(String url) throws MalformedURLException {
        return new URL(url).getHost().equals("example.com");
    }
}