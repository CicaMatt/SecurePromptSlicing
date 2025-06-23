import java.io.*;

import java.net.HttpURLConnection;

import java.net.URL;

import javax.servlet.http.*;

import org.apache.commons.fileupload.*;

import org.apache.commons.fileupload.disk.*;

import org.apache.commons.fileupload.servlet.*;

import org.apache.commons.io.output.*;

public class login_page extends HttpServlet {

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		resp.setContentType("text/html");
		PrintWriter out = resp.getWriter();
		out.println("<!DOCTYPE html>");
		out.println("<html>");
		out.println("<head>");
		out.println("<title>Login Page</title>");
		out.println("</head>");
		out.println("<body>");
		out.println("<h1>Welcome!</h1>");
		out.println("<form method='post' enctype='multipart/form-data' action='/do_login'>");
		out.println("Username: <input type='text' name='username'><br>");
		out.println("Password: <input type='password' name='password'><br><br>");
		out.println("<input type='submit' value='Login'>");
		out.println("</form>");
		out.println("</body>");
		out.println("</html>");
	}
}
public class do_login extends HttpServlet {

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		boolean isMultipart = ServletFileUpload.isMultipartContent(req);
		if (!isMultipart) {
			resp.sendError(HttpServletResponse.SC_BAD_REQUEST);
		} else {
			DiskFileItemFactory factory = new DiskFileItemFactory();
			ServletFileUpload upload = new ServletFileUpload(factory);
			try {
				List<FileItem> fields = upload.parseRequest(req);
				String username = "";
				String password = "";
				for (FileItem field : fields) {
					if ("username".equalsIgnoreCase(field.getFieldName())) {
						username = field.getString();
					} else if ("password".equalsIgnoreCase(field.getFieldName())) {
						password = field.getString();
					}
				}
				if (username.isEmpty() || password.isEmpty()) {
					resp.sendError(HttpServletResponse.SC_BAD_REQUEST);
				} else if (username.equals("admin") && password.equals("password")) {
					resp.sendRedirect("/admin_page");
				} else {
					resp.sendRedirect("/user_page");
				}
			} catch (Exception e) {
				resp.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
			}
		}
	}
}
public class index extends HttpServlet {

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		resp.setContentType("text/html");
		PrintWriter out = resp.getWriter();
		out.println("<!DOCTYPE html>");
		out.println("<html>");
		out.println("<head>");
		out.println("<title>Index Page</title>");
		out.println("</head>");
		out.println("<body>");
		out.println("<h1>Welcome!</h1>");
		out.println("<a href='/login_page'>Login</a><br>");
		out.println("</body>");
		out.println("</html>");
	}
}
public class user_page extends HttpServlet {

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		resp.setContentType("text/html");
		PrintWriter out = resp.getWriter();
		out.println("<!DOCTYPE html>");
		out.println("<html>");
		out.println("<head>");
		out.println("<title>User Page</title>");
		out.println("</head>");
		out.println("<body>");
		out.println("<h1>Welcome User!</h1>");
		out.println("<a href='/index'>Home</a><br>");
		out.println("</body>");
		out.println("</html>");
	}
}
public class admin_page extends HttpServlet {

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		resp.setContentType("text/html");
		PrintWriter out = resp.getWriter();
		out.println("<!DOCTYPE html>");
		out.println("<html>");
		out.println("<head>");
		out.println("<title>Admin Page</title>");
		out.println("</head>");
		out.println("<body>");
		out.println("<h1>Welcome Admin!</h1>");
		out.println("<a href='/index'>Home</a><br>");
		out.println("</body>");
		out.println("</html>");
	}
}