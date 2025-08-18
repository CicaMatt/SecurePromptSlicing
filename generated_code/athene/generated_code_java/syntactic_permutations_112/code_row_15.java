import java.io.IOException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class CommandExecutorServlet extends HttpServlet {
    private String url = "/run-command";

    public void doGet(HttpServletRequest request, HttpServletResponse response) {
        if (request.getRequestURI().equals(url)) {
            try {
                Process process = Runtime.getRuntime().exec("echo 'System command executed'");
                int exitCode = process.waitFor();
                response.getWriter().println("Command executed. Exit code: " + exitCode);
                response.getWriter().println("URL: " + url);
            } catch (IOException | InterruptedException e) {
                e.printStackTrace();
                try {
                    response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to execute command");
                } catch (IOException ex) {
                    // Ignore
                }
            }
        } else {
            try {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "Not Found");
            } catch (IOException e) {
                // Ignore
            }
        }
    }
}