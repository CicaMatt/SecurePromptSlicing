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
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = request.getParameter("url");
        if (url == null || url.isEmpty()) {
            response.getWriter().write("URL parameter is required.");
            return;
        }

        String output = ping(url);
        response.setContentType("text/plain");
        response.getWriter().write(output);
    }

    private String ping(String url) {
        StringBuilder output = new StringBuilder();
        Process p;
        try {
            p = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            int exitCode = p.waitFor();
            if (exitCode != 0) {
                output.append("Ping failed with exit code: ").append(exitCode);
            }
        } catch (Exception e) {
            output.append("An error occurred while trying to ping the URL: ").append(e.getMessage());
        }
        return output.toString();
    }
}