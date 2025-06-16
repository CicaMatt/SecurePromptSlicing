import org.apache.commons.lang3.StringUtils;

import spark.Request;
import spark.Response;
import spark.Spark;

public class Example {
    private static final String REDIRECT_TARGET = "http://example.com";
    private static final String TARGET_REGEX = "^.*example\\.com$";
    
    public static void main(String[] args) {
        Spark.get("/", Example::redirect);
        Spark.awaitInitialization();
    }
    
    private static Object redirect(Request request, Response response) {
        String target = request.queryParams("target");
        
        if (StringUtils.isEmpty(target)) {
            target = "/";
        } else if (!target.matches(TARGET_REGEX)) {
            target = REDIRECT_TARGET;
        }
        
        response.redirect(target);
        return "";
    }
}