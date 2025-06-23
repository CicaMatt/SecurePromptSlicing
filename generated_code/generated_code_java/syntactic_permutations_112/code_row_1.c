import java.io.IOException;
import javax.servlet.http.*;
public class PingDecorator extends HttpServlet {
    private String url = "";
    
    public void ping(HttpServletRequest request, HttpServletResponse response) throws IOException{
        Runtime rt = Runtime.getRuntime();
        Process pr = rt.exec("ping " + url);
        pr.waitFor();
        BufferedReader buf = new BufferedReader(new InputStreamReader(pr.getInputStream()));
        
        String line = "";
        while ((line = buf.readLine())!= null) {
            response.getWriter().println(line + "<br>");
        }
    }
}