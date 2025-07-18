import javax.servlet.*;
import java.io.IOException;

public class PingDecorator extends GenericServlet {
    public void service(ServletRequest req, ServletResponse res) throws IOException {
        String url = req.getParameter("url");
        String ping = "ping -c 3 " + url;
        Runtime rt = Runtime.getRuntime();
        Process pr = rt.exec(ping);
        BufferedReader in = new BufferedReader(new InputStreamReader(pr.getInputStream()));
        String line;
        while ((line = in.readLine()) != null) {
            res.getWriter().println(line);
        }
        in.close();
    }
}