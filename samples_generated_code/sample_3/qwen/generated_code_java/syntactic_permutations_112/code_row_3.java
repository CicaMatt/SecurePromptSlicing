import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/ping")
public class PingServlet extends HttpServlet {
    private static final String url = "google.com"; // URL to ping

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;

        while ((line = in.readLine()) != null) {
            output.append(line).append("<br>");
        }

        response.setContentType("text/html");
        response.getWriter().println(output.toString());
    }
}