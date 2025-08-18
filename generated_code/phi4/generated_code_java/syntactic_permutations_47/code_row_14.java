import java.io.File;
import javax.servlet.http.HttpServletRequest;
import org.springframework.stereotype.Component;
import org.springframework.web.method.HandlerMethod;
import org.springframework.web.servlet.HandlerInterceptor;

@Component
public class ImageFileCheckInterceptor implements HandlerInterceptor {

    private static final String IMAGES_DIR = "/path/to/images"; // Change this path to your images directory

    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        if (handler instanceof HandlerMethod) {
            HandlerMethod methodHandler = (HandlerMethod) handler;
            String requestUri = request.getRequestURI();

            if (requestUri.contains("/checkImage")) { // Change this to your specific URL pattern
                String filePath = IMAGES_DIR + requestUri.substring(requestUri.lastIndexOf('/') + 1);
                File file = new File(filePath);

                if (!file.exists()) {
                    response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found");
                    return false;
                }
            }
        }

        return true; // Continue with the execution
    }
}