import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.jsp.JspFactory;
import javax.servlet.jsp.JspException;
import javax.servlet.jsp.PageContext;
import javax.servlet.jsp.tagext.SimpleTagSupport;

public class TemplateRenderer {

    public String renderResponseFromEnv(Map<String, Object> env) throws JspException {
        HttpServletRequest request = (HttpServletRequest) env.get("request");
        String name = request.getParameter("name");

        String template = (String) env.get("template");

        SimpleTagSupport tagSupport = new SimpleTagSupport() {
            @Override
            public void doTag() throws JspException, java.io.IOException {
                PageContext pageContext = (PageContext) getJspContext();
                pageContext.getOut().print(template.replace("${name}", name));
            }
        };

        try {
            javax.servlet.jsp.JspFactory.getDefaultFactory().invoke(tagSupport, new PageContext((javax.servlet.ServletRequest) env.get("request"), null, JspFactory.getDefaultFactory(), tagSupport, JspFactory.DEFAULT_BUFFER, false));
        } catch (Exception e) {
            throw new JspException("Error rendering template", e);
        }

        return (String) env.get("response");
    }

    public String home(Map<String, Object> env) throws JspException {
        return renderResponseFromEnv(env);
    }
}