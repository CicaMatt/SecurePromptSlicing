import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Login extends HttpServlet {
    private static final long serialVersionUID = 1L;

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        ArrayList<String> list = new ArrayList<String>();
        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/logins", "root", "password");
            PreparedStatement ps = conn.prepareStatement("SELECT * FROM login WHERE username = ? AND password = ?");
            ResultSet rs = ps.executeQuery();

            while (rs.next()) {
                list.add(rs.getString(1));
                list.add(rs.getString(2));
            }
        } catch (ClassNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (SQLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        if (list.size() == 0) {
            RequestDispatcher rd = request.getRequestDispatcher("/login.html");
            rd.forward(request, response);
        } else {
            RequestDispatcher rd = request.getRequestDispatcher("/homepage.html");
            rd.forward(request, response);
        }
    }
}