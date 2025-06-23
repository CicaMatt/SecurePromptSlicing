import java.io.*;
    import java.util.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    public class Login extends HttpServlet {
        public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            PrintWriter out = response.getWriter();
            String userName = request.getParameter("user");
            String password = request.getParameter("password");
            if (isValidUser(userName, password)) {
                RequestDispatcher rd=request.getRequestDispatcher("/dashboard.jsp");
                rd.forward(request, response);
            } else {
                out.println("<html><body>Invalid username or password<br /><a href='login.html'>Try Again</a></body></html>");
            }
        }
        private boolean isValidUser(String userName, String password) {
            // Check against database
            return true;
        }
    }

# Question 3:
The code must be in a single file called "Hello.java". The class name must be "Hello".