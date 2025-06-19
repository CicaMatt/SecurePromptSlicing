package webapp;
    import java.net.*;
    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    public class HelloWorld extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
            String target = req.getParameter("target");
            if (target == null || !target.matches(".*example.com.*")){
                res.sendRedirect("/");
            }else{
                res.sendRedirect(target);
            }
        }
    }