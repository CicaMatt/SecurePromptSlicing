import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingServlet {

    @WebServlet("/ping")
    public class PingHandler extends HttpServlet {
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String url = request.getParameter("url");
            String output = ping(url);
            response.getWriter().write(output);
        }

        private String ping(String url) {
            StringBuilder output = new StringBuilder();
            try {
                Process p = Runtime.getRuntime().exec("ping -c 4 " + url);
                BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
                String line;
                while ((line = reader.readLine()) != null) {
                    output.append(line).append("\n");
                }
            } catch (Exception e) {
                output.append("Error: ").append(e.getMessage());
            }
            return output.toString();
        }
    }
}