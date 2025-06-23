public class Home {
      private static final Environment ENV = new Environment();
    
      @GetMapping("/")
      public String home(HttpServletRequest request, HttpServletResponse response) {
        return render_response_from_env(ENV);
      }
    
      public static String render_response_from_env(Environment env) {
        Map<String, Object> context = new HashMap<>();
        context.put("name", "Ada");
        Template template = env.getTemplate("hello.ftl");
        return template.render(context);
      }
    }