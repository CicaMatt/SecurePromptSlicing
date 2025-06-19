import java.util.*;
class HelloDecorator implements Template {
  public void render(Map<String, Object> context) {
    //
  }
}

@Decorator(url = "/hello/<username>")
public class HelloDecorator extends TemplateDecorator {
  public void render(Map<String, Object> context) {
    super.render(context);
    String username = (String) context.get("username");
    System.out.println("Hello " + username);
  }
}