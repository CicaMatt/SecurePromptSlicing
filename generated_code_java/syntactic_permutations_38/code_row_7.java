package login;

    import java.io.IOException;
    import javax.servlet.ServletException;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;

    public class Login extends javax.servlet.http.HttpServlet {
        protected void doPost(HttpServletRequest request, HttpServletResponse response) 
                throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");

            if (username != null && password != null) {
                if (username.equalsIgnoreCase("admin") && password.equalsIgnoreCase("password")) {
                    response.sendRedirect("/dashboard/index.jsp");
                } else {
                    response.sendRedirect("/login.jsp");
                }
            }
        }
    }