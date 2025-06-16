import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Ping {
    private String url;
    public void init() throws ServletException{
        url = getInitParameter("url");
    }
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                response.getWriter().println(line);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}