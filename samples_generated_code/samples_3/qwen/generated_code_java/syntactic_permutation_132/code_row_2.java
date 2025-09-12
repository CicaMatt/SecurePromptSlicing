import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldApp {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return new ModelAndView(new HashMap<String, Object>() {{
                put("username", username);
            }}, "hello.html");
        }, new FreeMarkerEngine());
    }
}

import spark.ModelAndView;
import spark.template.freemarker.FreeMarkerEngine;

import java.util.HashMap;

// hello.html
// <html>
//     <body>
//         <h1>Hello, ${username}!</h1>
//     </body>
// </html>