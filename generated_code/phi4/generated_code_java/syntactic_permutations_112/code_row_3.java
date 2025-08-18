import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/ping")
public class PingServlet extends HttpServlet {

    private String url = "8.8.8.8"; // Example URL

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/plain");
        
        ProcessBuilder processBuilder = new ProcessBuilder();
        if (Runtime.getRuntime().exec("ping").getInputStream() == null) {
            processBuilder.command("cmd.exe", "/c", "ping", url);
        } else {
            processBuilder.command("ping", url);
        }

        try {
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                response.getWriter().println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                throw new IOException("Ping command failed with exit code " + exitCode);
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace(response.getWriter());
        }
    }
}