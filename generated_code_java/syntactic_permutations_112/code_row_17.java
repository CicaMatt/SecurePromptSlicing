import java.io.*;
import javax.servlet.*;

public class Ping extends HttpServlet { 
    private String url;
    
    public void init(ServletConfig config) throws ServletException { 
        this.url = config.getInitParameter("URL");
    }

    public void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException{ 
        Runtime rt = Runtime.getRuntime();
        Process proc = rt.exec("ping -c 1 " + url);

        InputStream stdIn = proc.getInputStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(stdIn));
        String line;
        while ((line = reader.readLine()) != null) {
            resp.getWriter().println(line);
        }
    } 
}