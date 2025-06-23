import java.lang.*; 

@WebServlet("/ping") 
public class Ping extends HttpServlet{ 
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException { 
        String url = req.getRequestURL().toString(); 
        Process p = Runtime.getRuntime().exec("ping " + url); 
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream())); 
        String inputLine; 
        while ((inputLine = in.readLine()) != null) { 
            System.out.println(inputLine); 
        } 
    } 
}