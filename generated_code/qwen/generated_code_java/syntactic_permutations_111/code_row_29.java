import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/ping")
public class PingServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String url = request.getParameter("url");
        if (url != null && !url.isEmpty()) {
            try {
                Process process = Runtime.getRuntime().exec("ping " + url);
                BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                StringBuilder output = new StringBuilder();
                String line;
                while ((line = reader.readLine()) != null) {
                    output.append(line).append("\n");
                }
                response.getWriter().write(output.toString());
            } catch (Exception e) {
                response.getWriter().write("Error executing ping command: " + e.getMessage());
            }
        } else {
            response.getWriter().write("URL parameter is missing or empty.");
        }
    }
}