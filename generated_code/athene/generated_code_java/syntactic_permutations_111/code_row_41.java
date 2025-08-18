import java.io.BufferedReader;
import java.io.InputStreamReader;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/ping")
public class PingServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String url = request.getParameter("url");
        String output = executePingCommand(url);
        response.getWriter().write(output);
    }

    private String executePingCommand(String url) {
        StringBuilder output = new StringBuilder();
        try {
            Process p = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        } catch (IOException e) {
            output.append("Error: ").append(e.getMessage());
        }
        return output.toString();
    }
}