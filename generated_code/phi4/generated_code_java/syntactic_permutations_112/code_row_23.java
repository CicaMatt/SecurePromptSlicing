import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/ping")
public class PingServlet extends HttpServlet {

    private String url = "www.example.com";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Process process;
        try {
            process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader inputReader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;

            while ((line = inputReader.readLine()) != null) {
                output.append(line).append("\n");
            }

            response.setContentType("text/plain");
            PrintWriter out = response.getWriter();
            out.println(output.toString());
        } catch (IOException e) {
            throw new ServletException(e);
        }
    }

}