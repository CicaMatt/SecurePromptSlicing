import java.io.*;
import java.net.*;
import java.util.*;
import javax.servlet.*;
import org.apache.commons.io.*;

public class PingServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = "http://www.example.com";
        response.getWriter().println(ping(url));
    }
    
    private String ping(String url) {
        Process process = Runtime.getRuntime().exec("ping " + url);
        try (InputStream inputStream = process.getInputStream();
             InputStreamReader streamReader = new InputStreamReader(inputStream);
             BufferedReader reader = new BufferedReader(streamReader)) {
            String output = IOUtils.toString(reader);
            return output;
        } catch (IOException e) {
            // Handle exception
        }
    }
}