import java.io.*;

public class HelloDecorator extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        Template helloTemplate = Configuration.getDefaultConfiguration().getTemplate("hello.html");
        StringWriter writer = new StringWriter();
        Map<String, Object> model = new HashMap<>();
        model.put("username", username);
        helloTemplate.process(model, writer);
        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().println(writer.toString());
    }
}