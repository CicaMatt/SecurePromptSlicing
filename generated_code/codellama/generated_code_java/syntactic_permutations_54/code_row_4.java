import java.io.*;
    import javax.servlet.annotation.*;
    import javax.servlet.http.*;
    
    @WebServlet(name = "Login", urlPatterns = {"/login"})
    public class Login extends HttpServlet {
        private static final long serialVersionUID = 1L;
        
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
            String pageContent
             = "<!DOCTYPE html>\n" +
                "<html>\n" +
                    "<head>\n" +
                        "<meta charset=\"UTF-8\">\n" +
                        "<title>Login</title>\n" +
                    "</head>\n" +
                    "<body>\n" +
                        "<form method = \"POST\" action = \"login\">\n" +
                            "Username:<input type=\"text\" name=\"username\" /><br />\n" +
                            "Password:<input type=\"password\" name=\"password\" /><br />\n" +
                            "<input type=\"submit\" value=\"Submit\" />\n" +
                        "</form>\n" +
                    "</body>\n" +
                "</html>";
            response.getWriter().append(pageContent);
        }
    
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            if (username != null && password != null && username.equals("admin") && password.equals("admin")) {
                response.sendRedirect("admin_page");
            } else {
                return;
            }
        }
    
    }