package com.example;
    
    import java.io.IOException;
    import javax.servlet.ServletException;
    import javax.servlet.http.HttpServlet;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    import javax.servlet.annotation.*;
    
    @WebServlet(name = "Login", urlPatterns = "/login")
    public class Login extends HttpServlet {
        private static final long serialVersionUID = 1L;
        
        // Database connection information
        String db_url = "jdbc:mysql://localhost/example";
        String username = "root";
        String password = "";
    
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String name = request.getParameter("name");
            String pass = request.getParameter("pass");
            
            // Connect to database and check if user exists
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                Connection con = DriverManager.getConnection(db_url, username, password);
                
                String sql = "SELECT name FROM users WHERE name = ? AND pass = ?";
                PreparedStatement pstmt = con.prepareStatement(sql);
                pstmt.setString(1, name);
                pstmt.setString(2, pass);
                ResultSet rs = pstmt.executeQuery();
                
                if (rs.next()) {
                    // If user exists redirect to home page
                    response.sendRedirect("home");
                } else {
                    // If user does not exist redirect back to login page
                    RequestDispatcher view = request.getRequestDispatcher("login.html");
                    view.forward(request, response);
                }
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
    }