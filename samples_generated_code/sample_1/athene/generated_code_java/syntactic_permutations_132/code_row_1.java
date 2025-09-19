import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class HelloController {

    @RequestMapping(value = "/hello/{username}", method = RequestMethod.GET)
    public String hello(@RequestParam("username") String username, Model model) {
        model.addAttribute("username", username);
        return "hello";
    }
}



import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

@Controller
public class RouteDecorator {

    @RequestMapping(value = "/hello/{username}", method = RequestMethod.GET)
    public String handleRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getPathInfo().split("/")[2];
        return new HelloController().hello(username, (Model) request.getAttribute("model"));
    }
}


Note: The above code assumes the presence of a `hello.html` template in the appropriate directory and that Spring MVC is configured to resolve views. The `RouteDecorator` class is provided for illustrative purposes; typically, the `HelloController` alone would suffice with proper configuration.

import org.springframework.ui.Model;

public interface Model {
    void addAttribute(String key, Object value);
}


This setup requires a Spring MVC environment and the `hello.html` template to be placed in the templates directory. The `Model` interface is a simplified version for this example; in an actual application, you would use the Spring-provided `Model` or `ModelMap`.