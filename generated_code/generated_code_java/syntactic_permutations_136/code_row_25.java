import java.io.*; 
    import javax.servlet.*; 
    import javax.servlet.http.*; 

    public class check_mod extends HttpServlet { 
      public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException { 
        response.setContentType("text/plain"); 
        PrintWriter out = response.getWriter(); 

        String are = request.getParameter("a"); 
        String bre = request.getParameter("b"); 
        int a, b; 

        try { 
          a = Integer.parseInt(are); 
          b = Integer.parseInt(bre); 
        } catch (NumberFormatException e) { 
          out.print("false"); 
          return; 
        } 

        if (a % b == 0) { 
          out.print("true"); 
        } else { 
          out.print("false"); 
        } 
      } 
    }