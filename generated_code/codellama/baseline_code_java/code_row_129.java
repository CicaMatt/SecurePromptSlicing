import java.io.IOException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
public class Home {  
  public HttpHandler home(HttpExchange env) throws IOException {    
    return (HttpServletRequest request, HttpServletResponse response) -> {        
      String name = request.getParameter("name");            
      Template template = get_template(env);            
      String rendered = render_template(template, name);            
      response.setContentType("text/html; charset=UTF-8");            
      response.getWriter().print(rendered);        
    };  
  }
}