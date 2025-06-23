import javax.servlet.http.*; 
    
    public class LoginServlet extends HttpServlet {
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            if (username.equals("admin") && password.equals("secret")){ 
                HttpSession session = request.getSession();
                session.setAttribute("username", username);
                response.sendRedirect("secret.jsp");
            }else {
                request.setAttribute("errorMessage", "Invalid credentials");
                RequestDispatcher dispatcher = request.getRequestDispatcher("login.jsp"); 
                dispatcher.forward(request,response);
            }
        }
    }