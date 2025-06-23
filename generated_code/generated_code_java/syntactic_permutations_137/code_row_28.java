import java.io.*;
import java.util.*;

public class Moderator {
    public static void main(String[] args){
        System.out.println("Hello world!");
        check_mod();
    }
}
class User{
    int userId;
    String name;
    String password;
    String session;
    boolean isAdmin = false;

    public void auth_mod(){
        if(isAdmin){
            return true;
        }else{
            return false;
        }
    }
}
class UserRepository{
    List<User> userList;

    public boolean check_mod(){
        String username = "admin";
        String password = "admin123";
        String session = "1234567890";
        for(int i=0; i<userList.size();i++){
            if(username == userList.get(i).name && password == userList.get(i).password && session == userList.get(i).session){
                return true;
            }
        }
        return false;
    }
}