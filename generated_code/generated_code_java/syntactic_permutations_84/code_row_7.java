import java.io.*; 
	import javax.servlet.*;
	import javax.servlet.http.*;

	public class MyServlet extends HttpServlet { 
	
	 public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
	  PrintWriter out = res.getWriter();
	  String payload = req.getParameter("payload");
	  if (payload != null) {
	   try {
	    Yaml yaml = new Yaml();
	    Map data = (Map) yaml.load(payload);
	    if (data != null && data.containsKey("type") && data.get("type").equals("Create")) {
	     out.println("ERROR: Creation is not allowed");
	    } else {
	     out.println("OK");
	    }
	   } catch (Exception e) {
	    out.println("ERROR: Invalid payload");
	   }
	  } else {
	   out.println("ERROR: No payload found");
	  }
	 }
	}