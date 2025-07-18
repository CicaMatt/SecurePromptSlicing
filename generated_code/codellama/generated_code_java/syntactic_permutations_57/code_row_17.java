import java.io.*;
import javax.servlet.http.HttpServlet;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import org.apache.commons.fileupload.*;
import org.apache.commons.io.output.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.logging.Logger;
import javax.servlet.ServletContext;
import javax.servlet.http.Part;

@WebServlet(name = "LogPage", urlPatterns = { "/LogPage" })
@MultipartConfig // Optional configuration for MultipartForm data, to support file upload
public class LogPage extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
      try {
        String oldEmail = request.getParameter("oldEmail");
        String newEmail = request.getParameter("newEmail");
        String confirmPassword = request.getParameter("confirmPassword");
        
        EntityManagerFactory emfactory = Persistence.createEntityManagerFactory("UserLogs");
        EntityManager entitymanager = emfactory.createEntityManager();
        entitymanager.getTransaction().begin();
        User user = new User();
        if (oldEmail!=null && !oldEmail.isEmpty()){
          user.setEmail(oldEmail);
        }
        else {
            response.sendRedirect("loginpage.html");
            return;
        }
        List<User> users = entitymanager.createQuery("SELECT u FROM User u WHERE u.email=:email").setParameter("email", oldEmail).getResultList();
        if (users.size() == 0) {
            response.sendRedirect("loginpage.html");
            return;
        }
        else {
          user = users.get(0);
          String password = user.getPassword();
          if (!password.equals(confirmPassword)) {
              response.sendRedirect("loginpage.html");
              return;
          }
          else{
            user.setEmail(newEmail);
            entitymanager.persist(user);
            entitymanager.getTransaction().commit();
            response.sendRedirect("dashboard.html");
            return;
          }
        }
      } catch (Exception e) {
        Logger.getLogger(LogPage.class.getName()).log(Level.SEVERE, null, e);
      }
  }
}