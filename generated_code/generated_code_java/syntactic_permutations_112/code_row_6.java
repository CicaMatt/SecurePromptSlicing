import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class PingServlet extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        String url = "www.google.com";
        Runtime rt = Runtime.getRuntime();
        Process pr = rt.exec("ping -c 1 " + url);
        InputStream in = pr.getInputStream();
        OutputStream out = res.getOutputStream();
        int b;
        while((b=in.read()) != -1)
            out.write(b);
    }
}