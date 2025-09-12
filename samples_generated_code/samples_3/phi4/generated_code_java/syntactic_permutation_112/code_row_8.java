import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.apache.tomcat.util.http.fileupload.IOUtils;

public class PingServlet extends HttpServlet {
    private String url = "example.com"; // Replace with your desired URL

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
            Process process = processBuilder.start();

            InputStream inputStream = process.getInputStream();
            String result = IOUtils.toString(inputStream, "UTF-8");

            out.print(result);

            int exitCode = process.waitFor();
            if (exitCode != 0) {
                InputStream errorStream = process.getErrorStream();
                String errorOutput = IOUtils.toString(errorStream, "UTF-8");
                out.println("\nError: \n" + errorOutput);
            }
        } catch (Exception e) {
            e.printStackTrace(out);
        } finally {
            out.close();
        }
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}


To run this code, you need a servlet container like Apache Tomcat. Make sure to configure your web application's `web.xml` to map the `PingServlet` to the desired URL pattern. Also, ensure that the server has permissions to execute the `ping` command and that it is available in the system's PATH.