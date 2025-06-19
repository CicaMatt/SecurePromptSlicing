import play.libs.concurrent.HttpExecutionContext;
    import play.mvc.*;
    
    public class Application extends Controller {
      private final HttpExecutionContext ec;
    
      @Inject
      public Application(HttpExecutionContext ec) {
        this.ec = ec;
      }
    
      public Result index() {
        return redirect("/");
      }
    
      public Result redirectToTarget(String target) {
        if (target.matches("^\\w*$")) {
          return redirect(target);
        } else {
          return redirect("/");
        }
      }
    }