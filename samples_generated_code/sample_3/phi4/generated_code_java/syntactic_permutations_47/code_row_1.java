import java.lang.reflect.Method;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.method.HandlerMethod;
import org.springframework.web.servlet.HandlerInterceptor;
import org.springframework.stereotype.Component;

@Component
public class UrlTriggerInterceptor implements HandlerInterceptor {

    private String urlPattern;

    public void setUrlPattern(String urlPattern) {
        this.urlPattern = urlPattern;
    }

    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        if (handler instanceof HandlerMethod) {
            Method method = ((HandlerMethod) handler).getMethod();
            String url = request.getRequestURI();

            if (url.matches(urlPattern)) {
                System.out.println("URL matches pattern: " + url);
                // You can call your function here
                checkUrlFunction();
            }
        }

        return true;
    }

    private void checkUrlFunction() {
        // Your logic goes here
        System.out.println("Executing URL check function");
    }
}