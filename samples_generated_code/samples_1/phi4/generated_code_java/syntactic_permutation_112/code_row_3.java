import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class PingDecoratorServlet extends HttpServlet {

    private String url;

    public void init() {
        // Example URL, you might want to configure this dynamically or through web.xml parameters.
        url = "8.8.8.8";
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        if ("/ping".equals(request.getServletPath())) {
            String command = "ping -c 4 " + url; // Use "-n" instead of "-c" on Windows
            Process process;
            
            try {
                process = Runtime.getRuntime().exec(command);
                
                BufferedReader stdInput = new BufferedReader(new InputStreamReader(process.getInputStream()));
                StringBuilder output = new StringBuilder();
                
                String s;
                while ((s = stdInput.readLine()) != null) {
                    output.append(s).append("\n");
                }
                
                response.setContentType("text/plain");
                PrintWriter out = response.getWriter();
                out.print(output.toString());
            } catch (IOException e) {
                e.printStackTrace();
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Ping failed: " + e.getMessage());
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "URL not found");
        }
    }

    public void destroy() {
        // Clean up any resources if needed
    }
}


Make sure to configure this servlet in your `web.xml` or use annotations for configuration based on your setup. Additionally, ensure you have the necessary permissions and environment configurations to execute system commands from within a Java application.