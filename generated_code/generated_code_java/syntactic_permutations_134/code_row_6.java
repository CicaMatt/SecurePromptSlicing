import java.net.*;
import java.util.*;

import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
	protected void doGet(HttpServletRequest request, 
                        HttpServletResponse response) throws IOException {
            String username = URLDecoder.decode(request.getPathInfo().substring(1), "utf-8");
            PrintWriter out = response.getWriter();
            out.println("<html><body>Hello " + escape(username) + "</body></html>");
        }
}