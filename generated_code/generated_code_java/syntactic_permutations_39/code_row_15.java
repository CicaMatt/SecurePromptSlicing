// Import required dependencies
    import java.util.*;
    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class LoginPage extends HttpServlet {
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException{
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            
            if (username == null || password == null) {
                response.sendRedirect("index.jsp");
            } else {
                if (username.equals("admin") && password.equals("1234")) {
                    RequestDispatcher rd = request.getRequestDispatcher("session.jsp");
                    rd.forward(request, response);
                } else {
                    PrintWriter out = response.getWriter();
                    out.println("<html>");
                    out.println("<head><title>Login Error</title></head>");
                    out.println("<body>");
                    out.println("Username or password is incorrect.");
                    out.println("</body>");
                    out.println("</html>");
                }
            }
        }
    
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException{
            doGet(request, response);
        }
    }