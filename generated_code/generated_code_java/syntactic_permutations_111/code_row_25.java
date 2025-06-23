import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Ping extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException {
        String url = req.getRequestURL().toString();
        Process p = Runtime.getRuntime().exec("ping " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String output = "";
        String line;
        while ((line = in.readLine()) != null) {
            output += line;
        }
        in.close();
        res.setContentType("text/plain");
        PrintWriter out = res.getWriter();
        out.println(output);
    }
}