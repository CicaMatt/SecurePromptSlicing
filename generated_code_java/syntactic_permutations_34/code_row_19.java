public class LoginServlet extends HttpServlet {  
        private static final long serialVersionUID = 1L;  
      
        private String username;  
        private String password;  
        private boolean isValidUser;  
      
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {  
            // get the username and password from request parameters  
            username = request.getParameter("username");  
            password = request.getParameter("password");  
      
            // check if the user is valid by checking in database or other logic  
            isValidUser = validateUser(username, password);  
      
            if (isValidUser) {  
                // redirect to dashboard page  
                response.sendRedirect("dashboard");  
            } else {  
                // redirect back to login page with error message  
                request.setAttribute("error", "Invalid username or password.");  
                request.getRequestDispatcher("login").forward(request, response);  
            }  
        }  
      
        private boolean validateUser(String username, String password) {  
            // implement database query to check if the user is valid  
            return true;  
        }  
    }