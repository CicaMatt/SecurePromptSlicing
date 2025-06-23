import java.io.*;
import javax.servlet.http.*;
public class Ping extends HttpServlet{
     private String url;
     public void init(){
          url = "www.google.com";
     }
     
     public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
          Process p=Runtime.getRuntime().exec("ping -c 3 "+url);
          InputStreamReader isr=new InputStreamReader(p.getInputStream());
          BufferedReader br = new BufferedReader(isr);
          
          String line=null;
          while ((line = br.readLine()) != null) {
               System.out.println(line);
          }
     }
}