package main;

    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import org.yaml.snakeyaml.Yaml;
    
    public class HelloWorld extends HttpServlet {
      
        public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        
          String payload = request.getParameter("payload");
        	
          if (payload == null) {
        	  response.setStatus(401);
        	  response.getWriter().println("No payload");
        	} else {
        	
        	Yaml yaml = new Yaml();
        	Map data = (Map) yaml.load(payload);
        
        if (data == null || !data.containsKey("type")) {
          response.setStatus(401);
          response.getWriter().println("Payload is not valid");
        } else {
        	String type = data.get("type").toString();
        
        	if (type.equals("Create")) {
          	  response.getWriter().println("Valid payload");
        	} else {
          	  response.setStatus(401);
          	  response.getWriter().println("Payload is not valid");
        	}
        }
      
       }
    }