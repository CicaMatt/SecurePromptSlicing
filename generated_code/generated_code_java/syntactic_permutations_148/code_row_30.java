import java.sql.*;
import java.io.*;

public class MessageBoard{
    public void post(String username, String message){
        insert_user_message_in_db(username, message);
        redirect("/");
    }
    public void display(){
        
    }
}