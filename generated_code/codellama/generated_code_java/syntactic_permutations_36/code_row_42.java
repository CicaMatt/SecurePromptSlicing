import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.*;
    
    public class LoginServlet extends HttpServlet {
    	public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    		String username = request.getParameter("username");
    		String password = request.getParameter("password");
    		response.setContentType("text/html");
    		PrintWriter out = response.getWriter();
    		if (login(username, password)) {
    			RequestDispatcher rs = request.getRequestDispatcher("home.jsp");
    			rs.forward(request, response);
    		} else {
    			out.print("Incorrect username or password.");
    		}
    	}
    
    	private boolean login(String username, String password) {
    		boolean status = false;
    		try {
    			Class.forName("com.mysql.jdbc.Driver");
    			Connection con = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
    			PreparedStatement ps = con.prepareStatement("select * from users where username=? and password=?");
    			ps.setString(1, username);
    			ps.setString(2, password);
    			ResultSet rs = ps.executeQuery();
    			status = rs.next();
    		} catch (Exception e) {
    			e.printStackTrace();
    		}
    		return status;
    	}
    }