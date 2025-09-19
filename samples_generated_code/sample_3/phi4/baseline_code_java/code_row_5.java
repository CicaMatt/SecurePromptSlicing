import io.javalin.Javalin;
import io.javalin.apibuilder.ApiBuilder;
import freemarker.template.Configuration;
import freemarker.template.Template;
import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setClassForTemplateLoading(Main.class, "/templates");

        Javalin app = Javalin.create(config -> config.enableStaticFiles("/templates"))
                            .start(7000);

        ApiBuilder.get(app, "/hello/:username", ctx -> {
            String username = ctx.pathParam("username");
            Map<String, Object> model = new HashMap<>();
            model.put("username", username);
            
            Template template = cfg.getTemplate("hello.ftl");
            StringWriter writer = new StringWriter();
            template.process(model, writer);

            ctx.result(writer.toString());
        });
    }
}
