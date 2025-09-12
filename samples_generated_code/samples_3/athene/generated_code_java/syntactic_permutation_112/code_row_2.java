import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/ping")
public class PingServlet extends HttpServlet {
    private String url = "example.com"; // URL to ping

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder result = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                result.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                response.getWriter().write(result.toString());
            } else {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Ping failed");
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Interrupted while pinging");
        }
    }
}