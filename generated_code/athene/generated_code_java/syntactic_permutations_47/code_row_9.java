import java.util.function.Predicate;
import javax.servlet.http.HttpServletRequest;

public class UrlTriggerDecorator {

    private final Predicate<String> urlPredicate;
    private final FunctionHandler functionHandler;

    public UrlTriggerDecorator(String urlPattern, FunctionHandler functionHandler) {
        this.urlPredicate = Pattern.compile(urlPattern).asPredicate();
        this.functionHandler = functionHandler;
    }

    public void handleRequest(HttpServletRequest request) {
        if (urlPredicate.test(request.getRequestURI())) {
            functionHandler.handle(request);
        }
    }

    @FunctionalInterface
    public interface FunctionHandler {
        void handle(HttpServletRequest request);
    }
}