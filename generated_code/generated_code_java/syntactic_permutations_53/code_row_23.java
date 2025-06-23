import java.io.\*;
import javax.servlet.\*;
import javax.servlet.http.\*;
import java.sql.\*;

public class Login extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        PrintWriter out = response.getWriter();
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/userdb", "root", "password");
            Statement stmt = con.createStatement();
            
            String userId = request.getParameter("userId");
            String password = request.getParameter("password");

            ResultSet rs = stmt.executeQuery("select * from users where userid='" + userId + "' and password='" + password + "'");

            if(rs.next()) {
                HttpSession session = request.getSession();
                String username = request.getParameter("username");
                
                if(session.getAttribute("userId") == null) {
                    out.println("<h1>Welcome " + username + "</h1>");
                } else if(rs.getString(3).equals("admin")) {
                    response.sendRedirect("admin.jsp");
                } else {
                    response.sendRedirect("user.jsp");
                }
            } else {
                out.println("<h1>Invalid userId or password</h1>");
            }
        } catch(Exception e) {
            out.println(e);
        }
    }
}