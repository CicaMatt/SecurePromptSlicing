import java.sql.*;
import javax.servlet.annotation.*;
import javax.servlet.http.*;
@WebServlet(name = "Login", urlPatterns = {"/login"})
public class Login extends HttpServlet {
    private String username;
    private String password;
    private Connection con;

    @Override
    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection(
                    "jdbc:mysql://localhost/login", "root", "password");
        } catch (ClassNotFoundException | SQLException ex) {
            Logger.getLogger(Login.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @Override
    public void destroy() {
        try {
            con.close();
        } catch (SQLException ex) {
            Logger.getLogger(Login.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String user = request.getParameter("user");
        String pass = request.getParameter("pass");
        if (user == null || pass == null) {
            RequestDispatcher rd = getServletContext().getRequestDispatcher("/login.jsp");
            rd.forward(request, response);
        } else {
            try {
                PreparedStatement ps = con.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
                ps.setString(1, user);
                ps.setString(2, pass);
                ResultSet rs = ps.executeQuery();
                if (rs.next()) {
                    response.sendRedirect("success.jsp");
                } else {
                    RequestDispatcher rd = getServletContext().getRequestDispatcher("/cant_login.jsp");
                    rd.forward(request, response);
                }
            } catch (SQLException ex) {
                Logger.getLogger(Login.class.getName()).log(Level.SEVERE, null, ex);
                RequestDispatcher rd = getServletContext().getRequestDispatcher("/internal_server_error.jsp");
                rd.forward(request, response);
            }
        }
    }
}