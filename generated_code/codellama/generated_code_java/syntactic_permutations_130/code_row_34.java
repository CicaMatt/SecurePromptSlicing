import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import freemarker.template.*;
public class HomeServlet extends HttpServlet{
	private Configuration configuration;
	public void init(ServletConfig servletConfig) throws ServletException{
		super.init(servletConfig);
		configuration = new Configuration();
		configuration.setDirectoryForTemplateLoading(new File("templates"));
		configuration.setObjectWrapper(new DefaultObjectWrapper());
	}
	public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		try {
			String name = request.getParameter("name");
			Template template = configuration.getTemplate("template.ftl");
			response.setContentType("text/html;charset=UTF-8");
			PrintWriter out = response.getWriter();
			Map<String, Object> data = new HashMap<String, Object>();
			data.put("name", name);
			template.process(data, out);
		} catch (TemplateException e) {
			e.printStackTrace();
		}
	}
}