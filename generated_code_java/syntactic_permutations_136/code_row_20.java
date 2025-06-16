import java.io.IOException;
    import javax.servlet.ServletException;
    import javax.servlet.http.*;
    public class CheckMod extends HttpServlet {
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            if (username.equals("admin") && password.equals("123456")){
                response.setContentType("text/plain");
                response.getWriter().print("true");
            } else {
                response.sendRedirect("/login?status=failure");
            }
        }
    }