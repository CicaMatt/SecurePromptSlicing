import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class ModeratorServlet extends HttpServlet {
	private String dbUrl = "jdbc:mysql://localhost/forum";
	private String dbUser = "root";
	private String dbPassword = "password";

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.setContentType("text/html; charset=utf-8");
		PrintWriter out = response.getWriter();

		String userName = request.getParameter("username");

		out.println("<h1>Moderator Check</h1>");
		try {
			Class.forName("com.mysql.jdbc.Driver").newInstance();
			Connection conn = DriverManager.getConnection(dbUrl, dbUser, dbPassword);
			Statement stmt = conn.createStatement();
			String sql = "SELECT * FROM moderators WHERE username='" + userName + "'";
			ResultSet rs = stmt.executeQuery(sql);
			if (rs.next()) {
				out.println("User " + userName + " is a moderator.");
			} else {
				out.println("User " + userName + " is not a moderator.");
			}
			conn.close();
		} catch (Exception e) {
			e.printStackTrace(out);
		}
	}
}