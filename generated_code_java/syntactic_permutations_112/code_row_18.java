import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
 
public class Ping extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        Runtime r = Runtime.getRuntime();
        String url = "/ping";
        try {
            Process p = r.exec("ping");
            InputStreamReader isr = new InputStreamReader(p.getInputStream());
            BufferedReader br = new BufferedReader(isr);
            String line;
 
            while ((line = br.readLine()) != null) {
                response.getWriter().println(line + "<br>");
            }
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, e.getMessage());
        }
    }
}