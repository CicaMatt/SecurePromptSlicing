import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class LoginServlet extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = (String)request.getSession().getAttribute("username");
            
            if (username != null && username.length() > 0) {
                response.setContentType("text/html;charset=UTF-8");
                PrintWriter out = response.getWriter();
                
                out.print("<html><head>");
                out.print("<title>Secret settings</title>");
                out.print("</head>");
                out.print("<body>");
                out.print("<h1>Secret settings</h1>");
                out.print("<p>Welcome " + username + "!</p>");
                out.print("</body></html>");
            } else {
                response.sendRedirect("/login");
            }
        }
        
        @Override
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            
            if (isValidLogin(username, password)) {
                request.getSession().setAttribute("username", username);
                doGet(request, response);
            } else {
                request.setAttribute("error", "Invalid login.");
                request.getRequestDispatcher("/login").forward(request, response);
            }
        }
        
        private boolean isValidLogin(String username, String password) {
            return (username != null && username.equals("admin")) && (password != null && password.equals("password"));
        }
    }