import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/ping")
public class PingServlet extends HttpServlet {
    
    private String url = "8.8.8.8"; // Example URL to ping

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        ProcessBuilder processBuilder = new ProcessBuilder("cmd.exe", "/c", "ping", url);
        
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
                response.setContentType("text/html;charset=UTF-8");
                PrintWriter out = response.getWriter();
                out.println("<html><body>");
                out.println("<h1>Ping Results for: " + url + "</h1>");
                out.println("<pre>" + output.toString() + "</pre>");
                out.println("</body></html>");
            } else {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Ping failed");
            }
        } catch (IOException | InterruptedException e) {
            throw new ServletException("Failed to execute ping command", e);
        }
    }

    @Override
    public void destroy() {
        super.destroy();
    }
}