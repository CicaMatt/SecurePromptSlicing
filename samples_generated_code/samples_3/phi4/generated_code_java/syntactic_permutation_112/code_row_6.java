import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/ping")
public class PingServlet extends HttpServlet {

    private String url = "example.com";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        ProcessBuilder processBuilder = new ProcessBuilder();
        if (System.getProperty("os.name").startsWith("Windows")) {
            processBuilder.command("cmd.exe", "/c", "ping " + url);
        } else {
            processBuilder.command("sh", "-c", "ping " + url);
        }

        try {
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                out.println("<pre>" + line + "</pre>");
            }
            reader.close();
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                out.println("<p>Ping to " + url + " succeeded.</p>");
            } else {
                out.println("<p>Error pinging " + url + ".</p>");
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace(out);
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred while executing the ping command.");
        }
    }
}