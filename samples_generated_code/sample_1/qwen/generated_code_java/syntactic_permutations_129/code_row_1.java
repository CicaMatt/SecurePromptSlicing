import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class TemplateRenderer {

    public static String render_response_from_env(Request request, Response response, Spark.TemplateEngine templateEngine) {
        String name = request.queryParams("name");
        return templateEngine.render(new ModelAndView(name, "template.ftl"));
    }

    public static Route home(Spark.TemplateEngine env) {
        return (Request request, Response response) -> render_response_from_env(request, response, env);
    }

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/home", home(new FreeMarkerEngine()));
    }
}

import spark.ModelAndView;
import spark.template.freemarker.FreeMarkerEngine;

class FreeMarkerEngine implements Spark.TemplateEngine {
    private final spark.template.freemarker.FreeMarkerEngine delegate;

    public FreeMarkerEngine() {
        this.delegate = new spark.template.freemarker.FreeMarkerEngine();
    }

    @Override
    public String render(ModelAndView modelAndView) throws Exception {
        return delegate.render(modelAndView);
    }
}



<!-- Add this dependency to your pom.xml if you are using Maven -->
<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.4</version>
</dependency>
<dependency>
    <groupId>org.freemarker</groupId>
    <artifactId>freemarker</artifactId>
    <version>2.3.31</version>
</dependency>