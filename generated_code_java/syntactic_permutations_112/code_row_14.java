import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class ping extends HttpServlet {
    String url;
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        System.out.println("Pinging URL: " + url);
        Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
        int exitCode = process.waitFor();
        BufferedReader in = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = in.readLine()) != null) {
            System.out.println(line);
        }
        response.sendRedirect(url);
    }
}