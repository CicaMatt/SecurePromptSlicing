import java.io.\*;
import java.net.\*;
import javax.servlet.http.\*;

public class Ping extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String url = getInitParameter("url");
        Process p = Runtime.getRuntime().exec("ping -c 3 " + url);
        InputStreamReader isr = new InputStreamReader(p.getInputStream());
        BufferedReader reader = new BufferedReader(isr);
        String line;
        while ((line = reader.readLine()) != null) {
            resp.getWriter().println(line);
        }
    }
}