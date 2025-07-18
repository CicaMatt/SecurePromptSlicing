import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class PingDecorator extends HttpServlet {
    String url;
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        ProcessBuilder builder = new ProcessBuilder("ping", url);
        builder.redirectOutput(new File("/dev/null"));
        builder.redirectError(new File("/dev/null"));
        try {
            int status = builder.start().waitFor();
            if (status == 0) {
                res.setStatus(HttpServletResponse.SC_OK);
                res.getWriter().println("Pinging " + url + " was successful");
            } else {
                res.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
                res.getWriter().println("Pinging " + url + " failed");
            }
        } catch (InterruptedException e) {
            throw new ServletException(e);
        }
    }
}