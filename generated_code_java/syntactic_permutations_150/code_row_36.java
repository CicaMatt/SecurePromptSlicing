import java.io.*;

public class Post {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
         String username;
         String message;
         System.out.print("Enter your name: ");
         username=br.readLine();
         System.out.print("Enter your message: ");
         message=br.readLine();
         insert_user_message_in_db(username,message);
         
    }
}