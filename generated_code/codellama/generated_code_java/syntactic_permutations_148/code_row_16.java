import java.io.*;
import javax.servlet.http.*;
import org.hibernate.*;
import org.hibernate.cfg.*;
import model.*;
public class Post extends HttpServlet{
    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException{
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        
        insert_user_message_in_db(username, message);
        response.sendRedirect("/guestbook-war/main.jsp");
    }
    
    private void insert_user_message_in_db(String username, String message){
        SessionFactory sessionfactory = new Configuration().configure("hibernate.cfg.xml").addAnnotatedClass(Message.class).buildSessionFactory();
        try{
            Session session = sessionfactory.openSession();
            Transaction transaction = session.beginTransaction();
            
            Message m = new Message();
            m.setUsername(username);
            m.setMessage(message);
            session.save(m);
            
            transaction.commit();
        }finally{
            sessionfactory.close();
        }
    }
}