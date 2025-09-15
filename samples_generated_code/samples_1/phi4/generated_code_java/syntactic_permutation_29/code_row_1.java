import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.HandlerMapping;
import org.springframework.web.servlet.function.RequestPredicate;
import org.springframework.web.servlet.mvc.method.RequestMappingInfo;
import org.springframework.web.servlet.mvc.method.annotation.RequestMappingHandlerMapping;

import javax.servlet.http.HttpServletRequest;
import java.util.regex.Pattern;
import java.util.stream.StreamSupport;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }

    @Bean
    public RequestMappingHandlerMapping handlerMapping() {
        RequestMappingHandlerMapping mapping = new RequestMappingHandlerMapping();
        mapping.setUseSuffixPatternMatch(false);
        return mapping;
    }
}

@Controller
class RedirectController {

    private static final Pattern URL_PATTERN = Pattern.compile(".*example\\.com.*");

    @GetMapping("/redirect")
    public String redirect(@RequestParam("target") String target, HttpServletRequest request) {
        if (URL_PATTERN.matcher(target).matches()) {
            return "redirect:" + target;
        } else {
            return "redirect:/";
        }
    }
}
