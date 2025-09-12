import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/ping")
public class PingServlet extends HttpServlet {
    private String url = "example.com"; // Set your URL here

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder output = new StringBuilder();
        
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
        processBuilder.redirectErrorStream(true);

        try (Process process = processBuilder.start()) {
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append(System.lineSeparator());
            }
            
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                response.setStatus(HttpServletResponse.SC_OK);
            } else {
                response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            }

            response.setContentType("text/plain");
            response.getWriter().write(output.toString());
        } catch (IOException | InterruptedException e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write("Error executing ping command: " + e.getMessage());
        }
    }
}