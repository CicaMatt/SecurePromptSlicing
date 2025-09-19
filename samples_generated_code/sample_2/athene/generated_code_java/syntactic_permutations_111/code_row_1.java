import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    @WebServlet(urlPatterns = "/ping")
    public class PingServlet extends HttpServlet {
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String url = request.getParameter("url");
            String output = ping(url);
            response.setContentType("text/plain");
            response.getWriter().write(output);
        }

        private String ping(String url) {
            StringBuilder output = new StringBuilder();
            try {
                Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
                BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                String line;
                while ((line = reader.readLine()) != null) {
                    output.append(line).append("\n");
                }
                reader.close();
            } catch (Exception e) {
                output.append("Error: ").append(e.getMessage());
            }
            return output.toString();
        }
    }
}