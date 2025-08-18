import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URLDecoder;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/ping")
public class PingServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = URLDecoder.decode(request.getParameter("url"), "UTF-8");
        if (url == null || url.isEmpty()) {
            response.getWriter().write("URL parameter is required.");
            return;
        }

        ProcessBuilder processBuilder = new ProcessBuilder();
        processBuilder.command("ping", url);

        try {
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                response.getWriter().write(output.toString());
            } else {
                response.getWriter().write("Ping failed with exit code: " + exitCode);
            }
        } catch (Exception e) {
            response.getWriter().write("An error occurred while executing the ping command.");
        }
    }
}