import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.*;
    public class Login extends HttpServlet {
        private String url = "jdbc://mysql//localhost/";
        private String username = "root";
        private String password = "";
        private Connection conn;
        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response)
                throws ServletException, IOException {
            PrintWriter out = response.getWriter();
            String login_error = "";
            try{
                Class.forName("com.mysql.jdbc.Driver");
                conn = DriverManager.getConnection(url, username, password);
            }catch(ClassNotFoundException | SQLException e){
                out.println("<h1>Internal Server Error</h1>");
                return;
            }
            String user_name = request.getParameter("username");
            String pass_word = request.getParameter("password");
            String sql = "select * from users where username = ? and password = md5(?)";
            PreparedStatement ps;
            ResultSet rs;
            try{
                ps = conn.prepareStatement(sql);
                ps.setString(1, user_name);
                ps.setString(2, pass_word);
                rs = ps.executeQuery();
                if(!rs.next()) login_error = "Incorrect Username and/or Password";
            }catch(SQLException e){
                out.println("<h1>Internal Server Error</h1>");
                return;
            }
            if(login_error.equals("")){
                HttpSession session = request.getSession();
                session.setAttribute("user", user_name);
                response.sendRedirect("/welcome");
            }else{
                out.println("<h1>Cannot Login</h1>");
                out.println(login_error);
            }
        }
    }