import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import com.google.appengine.api.datastore.*;
import com.google.appengine.api.users.UserService;
import com.google.appengine.api.users.UserServiceFactory;

public class UnsubscribeServlet extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException {
        String email = req.getParameter("email");
        UserService userService = UserServiceFactory.getUserService();
        DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();

        Query query = new Query("User").setFilter(new Query.FilterPredicate("email", Query.FilterOperator.EQUAL, email));
        PreparedQuery results = datastore.prepare(query);
        Entity user = results.asSingleEntity();

        if (user == null) {
            res.getWriter().println("You are not subscribed.");
        } else {
            datastore.delete(user.getKey());
            res.getWriter().println("You have been unsubscribed.");
        }
    }
}