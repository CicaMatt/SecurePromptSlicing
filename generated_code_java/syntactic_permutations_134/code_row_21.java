import java.util.HashMap;
import java.util.Map;
public class Routes {
  private Map<String, Function> routes = new HashMap<>();
  public void route(String url, Function function) {
    routes.put(url, function);
  }
  public Object call(String url, String[] arguments) throws Exception {
    return routes.get(url).apply(arguments);
  }
}
public class EscapeDecorator implements Function {
  private String original;
  public EscapeDecorator(String original) {
    this.original = original;
  }
  @Override
  public Object apply(Object argument) throws Exception {
    return escape((String) original);
  }
  private String escape(String text) {
    //TODO: convert special characters to HTML-safe sequences
    return "";
  }
}
public class HelloFunction implements Function {
  @Override
  public Object apply(Object argument) throws Exception {
    return hello((String) argument);
  }
  private String hello(String name) {
    return "Hello, " + name + "!";
  }
}