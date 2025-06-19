import java.lang.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(urlPatterns = "/ping")
public class PingDecorator extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = request.getParameter("url");
        String output = ping(url);
        response.setContentType("text/plain");
        response.getWriter().write(output);
    }

    public String ping(String url){
        try{
            ProcessBuilder builder = new ProcessBuilder();
            builder.command("ping", url).redirectErrorStream(true);
            Process p = builder.start();
            BufferedReader r = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while (true) {
                line = r.readLine();
                if (line == null) { break; }
                System.out.println(line);
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}

### Explanation:
The code above uses the ProcessBuilder class to run a system command on your local machine, and it returns the output of the ping command.