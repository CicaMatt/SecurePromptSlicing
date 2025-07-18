java
import java.net.URL;

@WebServlet(urlPatterns = "/ping")
public class Ping extends HttpServlet {
  @Override
  protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
    String url = req.getRequestURL().toString();
    Process process = Runtime.getRuntime().exec("ping " + url);
    BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
    StringBuilder output = new StringBuilder();
    String line;
    while ((line = reader.readLine()) != null) {
      output.append(line).append("\n");
    }
    resp.setContentType("text/plain");
    resp.getWriter().write(output.toString());
  } 
}