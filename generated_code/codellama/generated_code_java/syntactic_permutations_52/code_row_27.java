package login;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.io.*;
    
    public class LoginServlet extends HttpServlet {
        protected void doGet(HttpServletRequest request, 
                      HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            if (username == null || password == null) {
                response.setContentType("text/html");
                response.getWriter().println("<html><head></head><body>" +
                    "<form action=\".\" method=\"post\">" +
                    "Username:<br/> <input type=\"text\" name=\"username\"><br/>"+
                    "Password:<br/> <input type=\"password\" name=\"password\"><br/>" +
                    "<input type=\"submit\" value=\"Log in\">" + 
                    "</form></body></html>");
            } else if (username.equals("admin") && password.equals("1234")) {
                HttpSession session = request.getSession(true);
                session.setAttribute("username", username);
                response.sendRedirect("secret_page.jsp");
            } else {
                response.setContentType("text/html");
                response.getWriter().println("<html><head></head><body>" +
                    "<h1>Invalid credentials</h1>" + 
                    "</body></html>");
            }
        }
        
        protected void doPost(HttpServletRequest request, 
                       HttpServletResponse response) throws ServletException, IOException {
            doGet(request, response);
        }
    }