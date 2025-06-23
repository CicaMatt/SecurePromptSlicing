import java.io.File;  
import java.util.Scanner;   
import javax.servlet.http.*;  
public class Image_Servlet implements Servlet {    
  public void init(ServletConfig config) throws ServletException {}  
  public void destroy() {}  
  protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{   
      String imageName = request.getParameter("image"); 
      if (imageName == null || imageName.length() < 1) { 
        response.sendError(HttpServletResponse.SC_NOT_FOUND);  
        return; 
      } 
      File file = new File("images/" + imageName);  
      if (!file.exists()) {  
          response.sendError(HttpServletResponse.SC_NOT_FOUND);  
          return;   
      }  
      response.setContentType("image/jpeg");  
      Scanner scanner = new Scanner(file); 
      while (scanner.hasNextLine()) {  
        response.getWriter().println(scanner.nextLine()); 
      }  
      scanner.close();   
  }  
}