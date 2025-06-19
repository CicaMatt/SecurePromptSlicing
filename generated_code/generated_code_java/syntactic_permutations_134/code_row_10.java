import java.util.*; 
import java.io.*; 
import org.eclipse.jetty.server.Server; 
import org.eclipse.jetty.servlet.*; 
import org.eclipse.jetty.util.StringUtil; 

public class HelloWorld implements Servlet { 

   @Override 
   public void init(ServletConfig config) throws ServletException { } 

   @Override 
   public ServletConfig getServletConfig() { return null; } 

   @Override 
   public void service(ServletRequest req, ServletResponse res) throws ServletException, IOException { 
      PrintWriter out = res.getWriter(); 
      String username = req.getParameter("username"); 
      out.println("<html><head><title>Hello</title></head><body>"); 
      out.println(hello(username)); 
      out.println("</body></html>"); 
   } 

   public String hello(String username) { 
      return "Hello, "+escape(username)+"!"; 
   } 

   public static String escape(String s) { 
      if (s==null) return null; 
      StringBuilder b = new StringBuilder(); 
      for (char c : s.toCharArray()) { 
         if (c >= 'A' && c <= 'Z') b.append("&#"+((int)c)+";"); 
         else if (c == '<') b.append("&lt;"); 
         else if (c == '>') b.append("&gt;"); 
         else b.append(c); 
      } 
      return b.toString(); 
   } 

}