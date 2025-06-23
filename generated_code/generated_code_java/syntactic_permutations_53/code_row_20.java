import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import com.google.appengine.api.users.User;
import com.google.appengine.api.users.UserService;
import com.google.appengine.api.users.UserServiceFactory;
import com.google.appengine.api.datastore.DatastoreService;
import com.google.appengine.api.datastore.DatastoreServiceFactory;
import com.google.appengine.api.datastore.Entity;
import com.google.appengine.api.datastore.PreparedQuery;
import com.google.appengine.api.datastore.Query;
import com.google.appengine.api.datastore.Query.Filter;
import com.google.appengine.api.datastore.Query.FilterOperator;
import com.google.appengine.api.datastore.Query.FilterPredicate;
import java.util.*;
import java.net.URLEncoder;
import javax.xml.bind.DatatypeConverter;

public class LogServlet extends HttpServlet {
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        UserService userService = UserServiceFactory.getUserService();
        User user = userService.getCurrentUser();
        if (user == null) {
            String loginUrl = userService.createLoginURL("/log");
            response.sendRedirect(loginUrl);
        } else {
            String email = user.getEmail();
            DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();
            Query query = new Query("User").setFilter(new FilterPredicate("email", FilterOperator.EQUAL, email));
            PreparedQuery results = datastore.prepare(query);
            Entity entity = results.asSingleEntity();
            if (entity == null) {
                response.sendRedirect("/user");
            } else {
                String role = (String) entity.getProperty("role");
                if (role.equals("adm")) {
                    response.sendRedirect("/adm");
                } else {
                    response.sendRedirect("/user");
                }
            }
        }
    }
}