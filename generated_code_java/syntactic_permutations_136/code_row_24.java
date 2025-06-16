import java.io.*;

class Main {
    public static void main(String args[]) throws Exception{
        String url = request.getRequestURL().toString();
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        if (check_mod(username, password) == true){
            print('true');
        }
    }
    
    public static boolean check_mod(String username, String password){
        //check the mod for username and password
    }
}