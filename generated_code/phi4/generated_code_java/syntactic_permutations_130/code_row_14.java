import java.io.StringWriter;
import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.jsp.JspFactory;
import javax.servlet.jsp.PageContext;
import javax.servlet.jsp.SimpleJspFragment;
import javax.servlet.jsp.tagext.TagSupport;

public class WebApp {

    public static String renderResponseFromEnv(ServletContext env, HttpServletRequest request) throws Exception {
        String templateName = request.getParameter("name");
        
        JspFactory factory = JspFactory.getDefaultFactory();
        PageContext pageContext = factory.getPageContext(null, null, null, 0, true, JspWriter.DEFAULT_BUFFER, false);
        
        SimpleJspFragment fragment = new SimpleJspFragment(env.getResource(templateName), pageContext.getServletConfig().getServletContext());
        
        StringWriter writer = new StringWriter();
        fragment.invoke(pageContext, null);
        return writer.toString();
    }

    public static String home(ServletContext env, HttpServletRequest request) {
        try {
            return renderResponseFromEnv(env, request);
        } catch (Exception e) {
            return "Error: Unable to render response.";
        }
    }
}