import java.lang.*;

@WebServlet("/ping") 
public class Ping extends HttpServlet{  
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException{
        String url = request.getParameter("url");
        Process p = Runtime.getRuntime().exec("ping " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String inputLine;
        while ((inputLine = in.readLine()) != null) {
            response.getWriter().println(inputLine);
        } 
    }
}