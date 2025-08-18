import java.io.BufferedReader;
import java.io.InputStreamReader;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/ping")
public class PingServlet extends HttpServlet {
    private String url = "example.com";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        Process p = Runtime.getRuntime().exec("ping -c 1 " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String inputLine;
        StringBuilder result = new StringBuilder();
        while ((inputLine = in.readLine()) != null) {
            result.append(inputLine).append("\n");
        }
        in.close();

        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Ping Result for " + url + "</h1>");
        response.getWriter().println("<pre>" + result.toString() + "</pre>");
        response.getWriter().println("</body></html>");
    }
}