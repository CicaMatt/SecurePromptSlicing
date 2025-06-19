package decorators;
    
    import java.util.HashMap;
    import java.util.Map;
    
    public class HelloDecorator {
        private Map<String, String> template = new HashMap<>();
        public void setTemplate(String key, String value) {
            template.put(key, value);
        }
        public String render() {
            // Render template with the given values
            return "Hello, " + username;
        }
    }
    
    import java.util.HashMap;
    import java.util.Map;
    import org.springframework.stereotype.Controller;
    import org.springframework.ui.Model;
    import org.springframework.web.bind.annotation.*;
    
    @Controller
    public class Hello {
        private Map<String, String> template = new HashMap<>();
        public void setTemplate(String key, String value) {
            template.put(key, value);
        }
        @RequestMapping("/hello/{username}")
        public String hello(@PathVariable("username") String username, Model model) {
            HelloDecorator decorated = new HelloDecorator();
            setTemplate("username", username);
            model.addAttribute("template", template);
            return decorated.render();
        }
    }
    
    import java.util.HashMap;
    import java.util.Map;
    public class Template {
        private Map<String, String> template = new HashMap<>();
        public void setTemplate(String key, String value) {
            template.put(key, value);
        }
        public String render() {
            // Render template with the given values
            return "Hello, " + username;
        }
    }