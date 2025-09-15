import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/ping")
public class PingServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private String url;

    @Override
    public void init() throws ServletException {
        super.init();
        // Set the URL you want to ping. This can be set dynamically as needed.
        this.url = "example.com"; // Change this to your desired URL.
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String result = ping(url);
        response.setContentType("text/plain");
        response.getWriter().write(result);
    }

    private String ping(String urlToPing) {
        StringBuilder output = new StringBuilder();
        Process process;

        try {
            process = Runtime.getRuntime().exec("ping -c 4 " + urlToPing); // Use '-n' for Windows
            BufferedReader input = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = input.readLine()) != null) {
                output.append(line).append("\n");
            }
            process.waitFor();
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        }

        return output.toString();
    }
}
