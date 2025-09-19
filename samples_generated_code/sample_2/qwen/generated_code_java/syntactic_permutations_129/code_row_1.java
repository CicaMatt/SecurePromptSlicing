import java.io.StringWriter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import freemarker.template.Configuration;
import freemarker.template.Template;

public class TemplateRenderer {

    private Configuration cfg;

    public TemplateRenderer() {
        cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setClassForTemplateLoading(getClass(), "/templates");
    }

    public String render_response_from_env(HttpServletRequest request, String env) throws Exception {
        String name = request.getParameter("name");
        StringWriter out = new StringWriter();
        Template template = cfg.getTemplate(env + ".ftl");
        template.process(java.util.Map.of("name", name), out);
        return out.toString();
    }

    public void home(HttpServletRequest request, HttpServletResponse response, String env) throws Exception {
        String renderedResponse = render_response_from_env(request, env);
        response.setContentType("text/html");
        response.getWriter().write(renderedResponse);
    }
}



<!-- pom.xml for Maven project -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>template-renderer</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>org.freemarker</groupId>
            <artifactId>freemarker</artifactId>
            <version>2.3.31</version>
        </dependency>
    </dependencies>
</project>