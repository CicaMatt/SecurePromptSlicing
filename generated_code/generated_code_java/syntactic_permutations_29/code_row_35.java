import java.io.*;
    import java.net.*;
    import javax.servlet.*;
    import javax.servlet.http.*;

    public class Example extends HttpServlet {
        public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String target = request.getParameter("target");
            if(target != null && target.matches(".*example\\.com.*")){
                response.sendRedirect(target);
            } else {
                response.sendRedirect("/");
            }
        }
    }