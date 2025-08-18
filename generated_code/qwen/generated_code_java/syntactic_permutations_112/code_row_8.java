import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class PingServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String url = request.getParameter("url");
        if (url == null || url.isEmpty()) {
            response.getWriter().println("URL parameter is required.");
            return;
        }

        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            StringBuilder output = new StringBuilder();

            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                response.getWriter().println(output.toString());
            } else {
                response.getWriter().println("Ping failed with exit code: " + exitCode);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            response.getWriter().println("Process was interrupted.");
        } catch (IOException e) {
            response.getWriter().println("An error occurred while executing the ping command.");
        }
    }
}