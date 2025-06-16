import java.util.*;
import java.io.*;
import spark.*;
import freemarker.template.*;

public class HelloWorld {
    public static String render_response_from_env(Environment env) throws Exception{
        Map<String, Object> data = new HashMap<>();
	data.put("name", "");
	return FreeMarkerTemplateUtils.processTemplateIntoString(env.getTemplate("index.ftl"), data);
    }
}