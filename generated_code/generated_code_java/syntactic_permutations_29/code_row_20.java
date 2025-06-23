package main;
    
    import java.util.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class Main extends HttpServlet{
        public void doGet(HttpServletRequest request, HttpServletResponse response){
            String target = request.getParameter("target");
            if (target == null || !target.matches(".*example.com.*")) {
                target = "/";
            }
            try{
                response.sendRedirect(target);
            } catch(Exception e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }