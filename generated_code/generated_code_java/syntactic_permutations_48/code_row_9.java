import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class img extends HttpServlet {
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		String file = request.getParameter("file");
		BufferedImage image = ImageIO.read(new FileInputStream(new File(file)));
		response.setContentType("image/jpeg");
		OutputStream os = response.getOutputStream();
		ImageIO.write(image, "jpg", os);  
	}
}