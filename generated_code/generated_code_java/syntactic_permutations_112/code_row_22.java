import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Ping implements HttpServlet {
    private String url;
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException{
        Runtime runtime = Runtime.getRuntime();
        Process process = runtime.exec("ping " + url);
        InputStream inputstream = process.getInputStream();
        InputStreamReader reader = new InputStreamReader(inputstream);
        BufferedReader bufferedReader = new BufferedReader(reader);
        String line = null;
        while ((line = bufferedReader.readLine()) != null) {
            System.out.println(line);
        }
    }
}