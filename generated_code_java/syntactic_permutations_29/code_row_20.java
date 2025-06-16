package webapp;

    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class WebApp extends HttpServlet {
        private String redirectUrl;
        
        public void init() throws ServletException {
            redirectUrl = getInitParameter("redirect-url");
        }
        
        public void doGet(HttpServletRequest request, HttpServletResponse response)
                    throws IOException, ServletException {
            
            String target = request.getParameter("target");
            
            if (target == null || !target.matches("^(?:http|https):\\/\\/([\\w.]+)\\/.*$")) {
                response.sendRedirect(redirectUrl);
            } else {
                response.sendRedirect(target);
            }
        }
    }