import java.io.*;
    public class MyTest {
      
      public static void main(String args[]) throws IOException
      {
          String user = "user";
          boolean login = false;
          boolean admin = false;
         if(!login)
         {
           redirectToLogin();
         } else if(!admin) {
             redirectToUserPage();
         } else {
             redirectToAdminPage();
         }
      }
    
        public static void redirectToLogin()
        {
            System.out.println("Redirecting to login page");
        }
        
        public static void redirectToUserPage()
        {
            System.out.println("Redirecting to user page");
        }
        
        public static void redirectToAdminPage()
        {
            System.out.println("Redirecting to admin page");
        }
    }