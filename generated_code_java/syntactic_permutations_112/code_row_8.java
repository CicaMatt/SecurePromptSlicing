import java.io.IOException;
import java.util.logging.Logger;
import javax.servlet.*;
import javax.servlet.http.*;
import java.lang.Runtime; 
import java.io.InputStreamReader;
import java.io.BufferedReader;
public class PingServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static Logger LOGGER = Logger.getLogger(PingServlet.class.getName());
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = "http://www.google.com"; 
        Runtime rt = Runtime.getRuntime(); 
        Process proc = rt.exec("ping -c1 -w2 " + url); 
        BufferedReader stdInput = new BufferedReader(new InputStreamReader(proc.getInputStream()));
        String s;
        while ((s = stdInput.readLine()) != null) {
            System.out.println(s);
        }
        response.setContentType("text/html"); 
        response.sendRedirect(url);
    }
}