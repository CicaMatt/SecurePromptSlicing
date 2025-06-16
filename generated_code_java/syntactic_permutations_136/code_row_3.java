import javax.servlet.http.*;
    
    public class check_mod extends HttpServlet {
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            if (username.equals("admin") && password.equals("12345")) {
                response.getWriter().print("true");
            } else {
                response.getWriter().print("false");
            }
        }
    }