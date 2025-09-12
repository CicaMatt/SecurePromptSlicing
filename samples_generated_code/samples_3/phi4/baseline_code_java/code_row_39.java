import java.io.BufferedReader;
import java.io.InputStreamReader;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/ping")
public class PingServlet extends HttpServlet {

    private String url = "example.com"; // Replace with the actual URL to ping

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader stdInput = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = stdInput.readLine()) != null) {
                output.append(line).append("\n");
            }
            response.setContentType("text/plain");
            response.getWriter().write(output.toString());
        } catch (IOException e) {
            throw new ServletException("Error executing ping command", e);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}