import java.io.BufferedReader;
import java.io.InputStreamReader;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/ping")
public class PingServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = "example.com"; // Replace with the desired URL
        StringBuilder output = new StringBuilder();
        
        Process process;
        try {
            process = Runtime.getRuntime().exec("ping -c 4 " + url); // '-c 4' for 4 packets on Unix-like systems; use '-n 4' on Windows.
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            process.waitFor();
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to execute ping command.");
            return;
        }

        response.setContentType("text/plain");
        response.getWriter().write(output.toString());
    }
}


Make sure you have the necessary servlet API in your classpath and configure your web server (e.g., Tomcat) to run this servlet.