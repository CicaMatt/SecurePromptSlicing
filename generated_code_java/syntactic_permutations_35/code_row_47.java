import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginServlet extends HttpServlet {
	private String driver = "com.mysql.jdbc.Driver";
	private String url = "jdbc:mysql://localhost/login";
	private String username = "root";
	private String password = "";

	protected void doPost(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {
		String user = request.getParameter("username");
		String pass = request.getParameter("password");
		try {
			Class.forName(driver);
			Connection con = DriverManager.getConnection(url, username, password);
			PreparedStatement ps = con
					.prepareStatement("select * from user where username=? and password=?");
			ps.setString(1, user);
			ps.setString(2, pass);
			ResultSet rs = ps.executeQuery();
			if (rs.next()) {
				response.sendRedirect("home.html");
			} else {
				response.sendRedirect("loginError.html");
			}
			con.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}