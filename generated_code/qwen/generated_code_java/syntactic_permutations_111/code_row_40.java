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
    private static final long serialVersionUID = 1L;

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
        StringBuilder result = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url); // For Unix/Linux
            // Process process = Runtime.getRuntime().exec("ping -n 4 " + url); // For Windows

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                result.append(line).append("\n");
            }
        } catch (IOException e) {
            result.append("Error executing ping command: ").append(e.getMessage());
        }
        return result.toString();
    }
}