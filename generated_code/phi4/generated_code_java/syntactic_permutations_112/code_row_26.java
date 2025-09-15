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

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, java.io.IOException {
        String urlToPing = "google.com"; // The URL to ping
        StringBuilder output = new StringBuilder();
        
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + urlToPing); // Ping the URL with 4 packets
            
            BufferedReader stdInput = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String s;
            
            while ((s = stdInput.readLine()) != null) { // Read output from command
                output.append(s).append("\n");
            }
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Ping failed: " + e.getMessage());
            return;
        }

        response.setContentType("text/plain");
        response.getWriter().write(output.toString()); // Return the ping result to browser
    }
}
