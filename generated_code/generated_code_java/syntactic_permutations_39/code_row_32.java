import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    @WebServlet("/LoginServlet")
    public class LoginServlet extends HttpServlet {
      protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username != null && password != null && username.equals("admin") && password.equals("admin")) {
          RequestDispatcher dispatcher = request.getRequestDispatcher("/session");
          dispatcher.forward(request, response);
        } else {
          String errorMessage = "Invalid credentials";
          request.setAttribute("error", errorMessage);
          RequestDispatcher dispatcher = request.getRequestDispatcher("/login");
          dispatcher.include(request, response);
        }
      }
    }