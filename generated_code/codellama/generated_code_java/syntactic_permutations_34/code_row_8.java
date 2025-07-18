import javax.servlet.http.*;
    import java.io.*;
    import javax.servlet.RequestDispatcher;
    @WebServlet("/login")
    public class Login extends HttpServlet {
    	private static final long serialVersionUID = 1L;
    	public void doPost(HttpServletRequest req, HttpServletResponse resp)
    		throws IOException, ServletException {
    		String username = req.getParameter("username");
    		String password = req.getParameter("password");
    		if (isUserValidated(username, password)) {
    			RequestDispatcher dispatcher =
    			req.getRequestDispatcher("dashboard.jsp");
    			dispatcher.forward(req, resp);
    		} else {
    			RequestDispatcher dispatcher =
    			req.getRequestDispatcher("login.html");
    			dispatcher.include(req, resp);
    		}
    	}
    	private boolean isUserValidated(String username, String password) {
    		// Fetch the details from the database and verify against the entered values
    		return true;
    	}
    }