import java.io.*;
import java.net.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class http_hello_page extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException, ServletException{
        String username = "";
        try (BufferedReader br = new BufferedReader(new InputStreamReader(req.getInputStream()))) {
            while ((line = br.readLine()) != null) username += line + "\n";
        } catch (IOException e) {}
        String outputbuf = "<html><head></head><body>Hello, " + username + "!</body></html>";
        try (OutputStream os = res.getOutputStream();) {
            os.write(outputbuf.getBytes());
        } catch (IOException e) {}
    }
}