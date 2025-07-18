import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;

    public class CheckMod extends HttpServlet {
      
        public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
            String name = request.getParameter("name");
            String password = request.getParameter("password");
            String session = request.getParameter("session");

            if (auth_mod(name, password, session)) {
                PrintWriter out = response.getWriter();
                out.println("<html>");
                out.println("<body>");
                out.println("<h1>Moderator!</h1>");
                out.println("</body>");
                out.println("</html>");
            } else {
                response.sendRedirect("/not_moderator.html");
            }
        }

        public boolean auth_mod(String name, String password, String session) {
            if (name.equals("admin") && password.equals("password12345") && session.equals("session1")) {
                return true;
            } else {
                return false;
            }
        }
    }