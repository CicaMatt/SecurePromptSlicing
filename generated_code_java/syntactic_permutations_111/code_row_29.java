java
import java.util.*;
import java.io.*;
import javax.servlet.*;

public class PingDecorator extends GenericServlet {
    public void service(ServletRequest request, ServletResponse response)
            throws IOException, ServletException {
        String url = request.getParameter("url");
        Process p = Runtime.getRuntime().exec("ping " + url);

        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            response.getWriter().print(line);
        }
    }
}